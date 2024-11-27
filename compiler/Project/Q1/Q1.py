import ast
from os.path import commonprefix
from itertools import groupby

inp = "{ 'E': ['E+T', 'T'], 'T': ['T*F', 'F'], 'F': ['(E)', 'id'] }"

inpg = ast.literal_eval(inp)

def eliminate_left_recursion(G):
    keys = list(G.keys())
    for i in range(len(keys)):
        Ai = keys[i]
        for j in range(i):
            Aj = keys[j]

            new_Ai_productions = []
            for production in G[Ai]:
                if production.startswith(Aj):
                    gamma = production[len(Aj):]
                    new_Ai_productions += [delta + gamma for delta in G[Aj]]
                else:
                    new_Ai_productions.append(production)

            G[Ai] = new_Ai_productions

        # حذف بازگشت چپ مستقیم
        alphas = []; betas = []
        for production in G[Ai]:
            if production.startswith(Ai):
                alphas.append(production[len(Ai):])
            else:
                betas.append(production)

        if len(alphas) > 0:
            Ai_prime = Ai + "`"
            Ai_productions = [beta + Ai_prime for beta in betas]
            Ai_prime_productions = [alpha + Ai_prime for alpha in alphas]
            Ai_prime_productions.append('')

            G[Ai] = Ai_productions
            G[Ai_prime] = Ai_prime_productions

    return G

def left_factor(G):
    to_check = list(G.keys())

    while len(to_check) > 0:
        A = to_check[0]
        prime_count = 1
        changed = True
        while changed:
            changed = False
            productions = G[A]
            productions_without_empty = productions.copy()
            has_empty = '' in productions
            if has_empty:
                productions_without_empty.remove('')

            grouped_by_first_letter = {k: list(v) for k, v in groupby(productions_without_empty, key=lambda x: x[0])}
            
            new_productions = []
            for k in grouped_by_first_letter:
                if len(grouped_by_first_letter[k]) >= 2:
                    common = commonprefix(grouped_by_first_letter[k])

                    A_prime = A + ('`' * prime_count)
                    prime_count += 1
                    new_productions.append(common + A_prime)

                    A_prime_productions = [x[len(common):] for x in grouped_by_first_letter[k]]
                    G[A_prime] = A_prime_productions
                    to_check.append(A_prime)

                    changed = True
                else:
                    new_productions.append(grouped_by_first_letter[k][0])
            if has_empty:
                new_productions.append('')
            G[A] = new_productions

        to_check = to_check[1:]

    return G

def transform(G):
    return eliminate_left_recursion(left_factor(G))

print(transform(inpg))