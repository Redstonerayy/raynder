import json
import sys
from multiprocessing import Process
import git
import os
import zip

# get depfile data from file
depfilepath = sys.argv[1]
depfile = open(depfilepath)
depdata = json.load(depfile)

# make dir
if not os.path.exists("deps"):
    os.mkdir("deps")

# loop over deps
# git deps
# spawn threads
gitprocs = []
for dep in depdata["git"]:
    name = dep.split("/")[-1].replace(".git", "").lower()
    gitprocs.append(Process(target=git.CloneOrUpdate, args=(dep, os.path.join("deps", name), name)))
    gitprocs[-1].start()

# join threads
for thread in gitprocs:
    thread.join()

# zips archives
# spawn threads
zipprocs = []
for dep in depdata["zip"]:
    name = name = dep.split("/")[-1].replace(".zip", "").lower()
    zipprocs.append(Process(target=zip.Fetch, args=(dep, os.path.join("deps", name), name)))
    zipprocs[-1].start()

for thread in zipprocs:
    thread.join()
