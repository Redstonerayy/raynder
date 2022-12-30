# copy files from corporateshark/bistro_materials to exteriour interior
import shutil
import os

shutil.copy(
    os.path.join("deps", "bistro_materials", "exterior.mtl"),
    os.path.join("deps", "exterior", "Exterior", "exterior.mtl")
)

shutil.copy(
    os.path.join("deps", "bistro_materials", "interior.mtl"),
    os.path.join("deps", "interior", "interior.mtl")
)
