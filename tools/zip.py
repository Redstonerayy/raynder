import urllib.request
import zipfile
import tempfile
import os

def Fetch(url, destination, name):
    if not os.path.exists(destination):
        # get data
        try:
            req = urllib.request.Request(url, headers={
                'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.116 Safari/537.36'
            })
            res = urllib.request.urlopen(req)
            data = res.read()
        except urllib.request.HTTPError as e:
            print("ERROR:", url, e.status, e.reason)
            return

        # save temp file
        try:
            path = os.path.join(tempfile.gettempdir(), name + ".zip")
            with open(path, "wb") as tmpf:
                tmpf.write(data)
        except FileNotFoundError:
            print("ERROR", path)
            return

        # extract zip file
        with zipfile.ZipFile(os.path.join(tempfile.gettempdir(), name + ".zip"), "r") as zipf:
            zipf.extractall(destination)

        print("Finshed fetching", destination)
    else:
        print(name, "is up to date!")