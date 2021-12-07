#Clear directory that stores outputted compressed matrix files

import os
import shutil
mydir = "CmpSpMfile"
shutil.rmtree(mydir)
os.makedirs(mydir)