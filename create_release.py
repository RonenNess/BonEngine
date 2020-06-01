import os
import shutil

# extract version from code
version = ""
for line in open("BonEngine/inc/BonEngine.h", 'r'):
    if "#define _BON_VERSION " in line:
        version = line.split("_BON_VERSION ")[-1].strip()
print ("Collect build folder for bon version: " + version)

# create the output folder (and remove old folder)
out_folder = "_build_temp"
if os.path.exists(out_folder):
    shutil.rmtree(out_folder)
os.mkdir(out_folder)

# add version to folder
out_folder_container = out_folder
out_folder = os.path.join(out_folder, "BonEngine-" + version)
os.mkdir(out_folder)

# copy includes
print ("Copy headers..")
shutil.copytree("BonEngine/inc", os.path.join(out_folder, "include"))

# create binary folders
print ("Create binary folders..")
bin_folder = os.path.join(out_folder, "lib")
bin_folder_x86 = os.path.join(bin_folder, "x86")
bin_folder_x64 = os.path.join(bin_folder, "x64")
os.mkdir(bin_folder)
os.mkdir(bin_folder_x86)
os.mkdir(bin_folder_x64)

# list of files to copy
files ="""BonEngine.dll
BonEngine.exp
BonEngine.lib
BonEngine.pdb
libFLAC-8.dll
libfreetype-6.dll
libjpeg-9.dll
libmodplug-1.dll
libmpg123-0.dll
libogg-0.dll
libopus-0.dll
libopusfile-0.dll
libpng16-16.dll
libtiff-5.dll
libvorbis-0.dll
libvorbisfile-3.dll
libwebp-7.dll
SDL2.dll
SDL2_image.dll
SDL2_mixer.dll
SDL2_ttf.dll
zlib1.dll""".split('\n')

# copy x86
print ("Copy x86 files..")
for file in files:
    shutil.copy(os.path.join("Release", file), os.path.join(bin_folder_x86, file))

# copy x64
print ("Copy x64 files..")
for file in files:
    shutil.copy(os.path.join("x64", "Release", file), os.path.join(bin_folder_x64, file))
    
# create zip and add to Build folder
print ("Compress and create output zip..")
out_zip = os.path.join("Build", "BonEngine-" + version)
shutil.make_archive(out_zip, 'zip', out_folder_container)

print ("Done! Output zip: " + out_zip + ".zip")