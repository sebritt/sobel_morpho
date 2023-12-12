# TP qualité logiciel - Git

*Ce TP sera réalisé sous Linux. Il nécessite l'accès à un compte GitHub.*

L'objectif de ce TP est de manipuler et comprendre quelques fonctionnalités avancées de Git. Pour cela, un projet Git est disponible au lien suivant: [https://github.com/QLOG-5EII/sobel_morpho](https://github.com/QLOG-5EII/sobel_morpho).

Le code contenu dans le dossier `src` applique un filtre de Sobel à une vidéo. Il est accompagné de fichiers CMake qui permettent de le compiler sur Linux ou Windows.

### Mise en place

Vous n'avez pas les droits d'accès au projet sur GitHub, ainsi il vous est possible de le cloner (puisque le projet est public), le modifier localement, mais pas de pousser vos modifications.

Pour pouvoir travailler sur le projet, vous devez faire un [fork](https://docs.github.com/en/get-started/quickstart/fork-a-repo).

Une fois le fork créé, vous pouvez cloner le projet sur votre machine et créer une branche de travail (avec le nom que vous souhaitez).

### Récupérer le travail d'une autre branche

Cela peut arriver que deux personnes travaillent sur des modifications nécessitant une correction similaire pour pouvoir avancer. Le mieux dans ce cas est de créer une branche spécifiquement pour cette correction et de la merger dans `main` afin que les deux puissent récupérer les modifications (avec un rebase) et avancer sur leurs tâches respectives.

Malheureusement, il arrive souvent que l'un d'eux ait déjà fait le correctif sur sa branche. Dans ce cas, l'autre peut attendre que la branche avec le correctif soit mergée dans `main`, mais cela peut prendre du temps. Une autre possibilité est de faire une copie des modifications d'une branche à l'autre. C'est cette seconde possibilité qui sera illustrée ici.

1. Le projet comporte une branche avec une modification à récupérer. La première étape consiste donc à lister les branches pour trouver son nom. Il ne devrait y avoir que trois branches : main, votre branche et la branche avec la modification. Une fois la branche identifiée, vous pouvez utiliser la fonction [`git log`](https://git-scm.com/docs/git-log) (avec les bons paramètres) pour afficher la liste des commits de cette branche.
1. Une fois que vous avez identifié le commit que vous souhaitez copier, vous pouvez utiliser la fonction [`git cherry-pick`](https://git-scm.com/docs/git-cherry-pick) pour effectuer la copie.
1. Le commit s'appelle *temp*, ce qui n'est pas terrible. Pour ce faire, on va utiliser la commande [`git rebase -i`](https://git-scm.com/docs/git-rebase) pour modifier l'historique de notre branche et changer le nom du commit. *Il peut être intéressant de noter que `HEAD~1` permet de pointer sur le commit précédent*

> **Note:** Les points 2 et 3 pourraient être effectués simultanément en utilisant l'option `--edit` de `git cherry-pick`. L'idée ici était d'avoir un exemple d'application avec `git rebase -i`.

### Modification du Sobel

À présent, on souhaite apporter des modifications au code. Comme évoqué précédemment, n'ayant pas le statut développeur sur le projet, vous ne pouvez pas pousser les modifications directement sur le projet original. C'est la raison pour laquelle le projet a été `fork`.

Pour proposer des modifications depuis un `fork`, il faut faire une pull request. C'est précisément ce que nous allons voir dans cette partie.

1. La fonction responsable d'appliquer le filtre de Sobel se trouve dans le fichier `src/sobel.c`. Modifiez cette fonction afin qu'elle applique un autre filtre que celui de Sobel (filtre moyenneur par exemple).
2. Créez un commit avec vos modifications.
3. Utilisez `git push` pour transférer vos modifications sur votre fork dans GitHub.
4. Sur le projet original, créez une pull request.

### Hooks

Certains projets sont développés par des centaines de personnes, chacune ayant son style de programmation. Il peut être difficile de s'y retrouver dans un code qui change sans cesse de style, c'est pourquoi certains projets imposent que les développeurs utilisent le même formateur de code afin d'unifier le style dans l'ensemble du projet.

En général, les IDE sont capables d'appeler ce genre de formateur et donc de gérer automatiquement le formattage (après chaque sauvegarde par exemple). Cependant comment être certain que l'ensemble des développeurs utilise bien le formateur et de la bonne façon ? Pour cela, une possibilité est d'utiliser les `git hooks`.

L'idée de cette section est de créer un hook qui vérifie que l'ensemble des fichiers sont correctement formatés et d'empêcher un commit le cas échéant.

1. Écrire un script bash qui vérifie que chaque fichier ajouté (en préparation d'un commit) est bien formaté. Pour cela, les commandes suivantes peuvent vous être utiles :
    - La commande `root=$(git rev-parse --show-toplevel)` permet de récupérer le chemin absolu du dossier git.
    - La commande `list=$(git diff --name-only --cached)` permet de récupérer la liste des fichiers ajoutés (staged).
    - La commande `clang-format $file` renvoie le contenu du fichier `$file` formaté.
    - Effectuer une boucle while itérant sur l'ensemble des lignes d'une variable `$list` se fait de la façon suivante:
    ```bash 
    while IFS= read -r line; do
    	echo "$line"
    done <<< "$list"
    ```

3. Renommez le fichier `.git/hooks/pre-commit.sample` par `.git/hooks/pre-commit` et remplacez son contenu par votre script. Pour empêcher un commit (dans le cas où un ou plusieurs fichiers ne sont pas bien formatés, le script doit renvoyer -1, en utilisant la commande `exit -1`, sinon, pour accepter l'exécution du commit, le script doit renvoyer 0.
4. Les hooks se trouvent dans le dossier .git et ne sont par conséquent pas versionnés dans le projet sur GitHub. Proposez et implémentez des solutions pour que votre hook soit présent sur l'ensemble des clones de votre projet. Faites une pull request avec votre proposition.