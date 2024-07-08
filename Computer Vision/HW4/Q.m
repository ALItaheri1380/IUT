clc, clear, close all;

dir_path = "./Q4/Puzzle_1_1200_1920/";
% dir_path = "./Q4/Puzzle_2_1200_1920/";
% dir_path = "./Q4/Puzzle_3_600_960/";
% dir_path = "./Q4/Puzzle_4_600_960/";

% Rotated Unrotated
puzzle_type = "Unrotated";
% 40 160
pieces = 40;



is_rotated = puzzle_type ~= "Unrotated";
puzzle_type = puzzle_type + "_" + num2str(pieces) + "/";

output = imread(dir_path + puzzle_type + "output.tif");
original = imread(dir_path + "Original.tif");
imshow(original);

min_pix = 4;
ck = 4;

if is_rotated
    patches = cell((pieces - 4) * 4, 6);
    k = 1;
    for i=1:pieces - 4
        img = imread(dir_path + puzzle_type + "Patch_" + num2str(i) + ".tif");
        rotations = [0 90 180 270];
        for r = rotations
            patches{(i-1) * 4 + 1 + r/90, 1} = imrotate(img, r);
            % used in output
            patches{(i-1) * 4 + 1 + r/90, 2} = false;
        
            % left column rgb hists
            patches{(i-1) * 4 + 1 + r/90, 3} = [imhist(img(:, 1:min_pix, 1)) imhist(img(:, 1:min_pix, 2)) imhist(img(:, 1:min_pix, 3))];
            % up row rgb hists
            patches{(i-1) * 4 + 1 + r/90, 4} = [imhist(img(1:min_pix, :, 1)) imhist(img(1:min_pix, :, 2)) imhist(img(1:min_pix, :, 3))];
            
            patches{(i-1) * 4 + 1 + r/90, 5} = [mean(img(:, 1:min_pix, 1), "all") mean(img(:, 1:min_pix, 2), "all") mean(img(:, 1:min_pix, 3), "all")];
            patches{(i-1) * 4 + 1 + r/90, 6} = [mean(img(1:min_pix, :, 1), "all") mean(img(1:min_pix, :, 2), "all") mean(img(1:min_pix, :, 3), "all")];
        end
    end
    pieces = (pieces - 4) * 4 + 4;
else
    patches = cell(pieces - 4, 6);
    for i=1:pieces - 4
    
        img = imread(dir_path + puzzle_type + "Patch_" + num2str(i) + ".tif");
        patches{i, 1} = img;
        % used in output
        patches{i, 2} = false;
    
        % left column rgb hists
        patches{i, 3} = [imhist(img(:, 1:min_pix, 1)) imhist(img(:, 1:min_pix, 2)) imhist(img(:, 1:min_pix, 3))];
        % up row rgb hists
        patches{i, 4} = [imhist(img(1:min_pix, :, 1)) imhist(img(1:min_pix, :, 2)) imhist(img(1:min_pix, :, 3))];
        
        patches{i, 5} = [mean(img(:, 1:min_pix, 1), "all") mean(img(:, 1:min_pix, 2), "all") mean(img(:, 1:min_pix, 3), "all")];
        patches{i, 6} = [mean(img(1:min_pix, :, 1), "all") mean(img(1:min_pix, :, 2), "all") mean(img(1:min_pix, :, 3), "all")];
    end
end


p_s = size(patches{1, 1}, 1);
for i = 1 : p_s : size(output, 1)
    for j = 1 : p_s : size(output, 2)
        if (i == 1 && j == 1) || (i == size(output, 1) - p_s + 1 && j == 1) ...
                || (i == 1 && j == size(output, 2) - p_s + 1) ...
                || (i == size(output, 1) - p_s + 1 && j == size(output, 2) - p_s + 1)
            continue
        end
        
        if j > 1
            right_hist = [imhist(output(i:i+p_s-1, j-min_pix:j-1, 1)) imhist(output(i:i+p_s-1, j-min_pix:j-1, 2)) imhist(output(i:i+p_s-1, j-min_pix:j-1, 3))];
        end
        if i > 1
            down_hist = [imhist(output(i-min_pix:i-1, j:j+p_s-1, 1)) imhist(output(i-min_pix:i-1, j:j+p_s-1, 2)) imhist(output(i-min_pix:i-1, j:j+p_s-1, 3))];
        end
        
        k = 1;
        chosens = cell(pieces - 4, 2);
        for x = 1:pieces-4
            if patches{x, 2}
                continue
            end
            
            nrm_column = 0;
            nrm_row = 0;
            if j > 1
                mc = [mean(output(i:i+p_s-1, j-min_pix:j-1, 1), "all") mean(output(i:i+p_s-1, j-min_pix:j-1, 2), "all") mean(output(i:i+p_s-1, j-min_pix:j-1, 3), "all")];
                nrm_column = norm(mc - patches{x, 5});
            end
            if i > 1
                mr = [mean(output(i-min_pix:i-1, j:j+p_s-1, 1), "all") mean(output(i-min_pix:i-1, j:j+p_s-1, 2), "all") mean(output(i-min_pix:i-1, j:j+p_s-1, 3), "all")];
                nrm_row = norm(mr - patches{x, 5});
            end
            
            nrm = norm([nrm_column nrm_row]);
            chosens{k, 1} = x;
            chosens{k, 2} = nrm;
            k = k+1;
        end
        while k <= pieces-4
            chosens{k, 1} = Inf;
            chosens{k, 2} = Inf;
            k = k+1;
        end
        chosens = sortrows(chosens, 2);
        chosens = cell2mat(chosens);
        chosens = chosens(1:ceil(size(chosens, 1) / ck), 1);

        chosen_img = -1;
        lowest_norm = -1;
        for x = 1:numel(chosens)
            k = chosens(x);
            if k == Inf
                continue;
            end

            nrm_column = 0;
            nrm_row = 0;
            if j > 1
                nrm_column = norm(right_hist - patches{k, 3});
            end
            if i > 1
                nrm_row = norm(down_hist - patches{k, 4});
            end

            nrm = norm([nrm_column nrm_row]);
            if nrm < lowest_norm || chosen_img == -1
                chosen_img = k;
                lowest_norm = nrm;
            end
        end
        if is_rotated
            base = (ceil(chosen_img / 4) - 1) * 4 + 1;
            for x=base:base+3
                patches{x, 2} = true;
            end
        end
        patches{chosen_img, 2} = true;

        output(i:i+p_s-1, j:j+p_s-1, :) = patches{chosen_img, 1}(:, :, :);
        imshow(output);
        pause(0.1);
    end
end