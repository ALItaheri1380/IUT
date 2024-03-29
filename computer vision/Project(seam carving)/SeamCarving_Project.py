from tqdm import trange
import numpy as np
import cv2
from imageio.v3 import imread, imwrite

def calculate_gradient_map(gray_image, ksize=3):
    gray_image = gray_image.astype(np.float32)
    gradient_x = cv2.Sobel(gray_image, cv2.CV_64F, 1, 0, ksize=ksize)
    gradient_y = cv2.Sobel(gray_image, cv2.CV_64F, 0, 1, ksize=ksize)
    energy_map = np.sqrt(gradient_x**2 + gradient_y**2)
    gradient_map = cv2.normalize(energy_map, None, 0, 255, cv2.NORM_MINMAX, cv2.CV_8U)
    return gradient_map


def calculate_energy(image):
    global seam_map, direction_map

    gray_img = image
    if np.ndim(image) != 2:
        gray_img = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)

    gradient_map = calculate_gradient_map(gray_img)
    energy_map = seam_map.astype(np.double) * 0.4 + gradient_map + 1.2 * direction_map
    return energy_map

def remove_column(image):
    global seam_map, direction_map

    rows, cols, _ = image.shape

    min_seam_matrix, backtrack_matrix = find_minimum_seam(image)
    mask = np.ones((rows, cols), dtype=bool)

    j = np.argmin(min_seam_matrix[-1])
    for i in reversed(range(rows)):
        mask[i, j] = False
        j = backtrack_matrix[i, j]

    seam_map = seam_map[mask].reshape((rows, cols-1))
    direction_map = direction_map[mask].reshape((rows, cols-1))
    mask = np.stack([mask] * 3, axis=2)
    image = image[mask].reshape((rows, cols - 1, 3))
    return image

def find_minimum_seam(image):
    rows, cols, _ = image.shape
    energy_map = calculate_energy(image)

    min_seam_matrix = energy_map.astype(np.uint32)
    backtrack_matrix = np.zeros_like(min_seam_matrix, dtype=int)

    for i in range(1, rows):
        for j in range(0, cols):
            if j == 0:
                index = np.argmin(min_seam_matrix[i-1, j:j + 2])
                backtrack_matrix[i, j] = index + j
                min_energy = min_seam_matrix[i-1, index + j]
            else:
                index = np.argmin(min_seam_matrix[i - 1, j - 1:j + 2])
                backtrack_matrix[i, j] = index + j - 1
                min_energy = min_seam_matrix[i - 1, index + j - 1]

            min_seam_matrix[i, j] += min_energy

    return min_seam_matrix, backtrack_matrix

def crop_image(image, scale_factor):
    _, cols, _ = image.shape
    new_cols = int(scale_factor * cols)

    for _ in trange(cols - new_cols):
        image = remove_column(image)
        imwrite("processing.png", image)

    return image

dataset_directory = './Samples dataset/'

def main():
    global dataset_directory, seam_map, direction_map

    scale_factor = float(input('Enter the scale factor: '))
    image_name = input('Enter the image name: ')
    output_filename = f'{image_name}_{scale_factor}.png'

    dataset_directory = dataset_directory + image_name + '/'
    seam_map = imread(dataset_directory + image_name + '_SMap.png')
    seam_map = cv2.normalize(seam_map, None, 0, 255, cv2.NORM_MINMAX, cv2.CV_8U)
    direction_map = imread(dataset_directory + image_name + '_DMap.png')
    direction_map = cv2.normalize(direction_map, None, 0, 255, cv2.NORM_MINMAX, cv2.CV_8U)

    img = imread(dataset_directory + image_name + '.png')

    output_image = crop_image(img, scale_factor)
    
    imwrite(output_filename, output_image)

if __name__ == '__main__':
    main()
