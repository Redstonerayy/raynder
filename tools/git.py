import subprocess
import os

def UpdateRepo(folderpath):
    os.chdir(folderpath)
    subprocess.run(["git", "pull"], stdout=subprocess.DEVNULL)

def CloneRepo(repourl, destination):
    subprocess.run(["git", "clone", repourl, destination], stdout=subprocess.DEVNULL)
    print("Finished Cloning", destination)

def CloneOrUpdate(repourl, destination, name):
    if os.path.exists(destination):
        UpdateRepo(destination)
        print(name, "is up to date!")
    else:
        CloneRepo(repourl, destination)