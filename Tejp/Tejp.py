from glob import iglob
import shutil
import os

## PACKING FUNCTIONS
def Concatenate(p_outputFile ,p_targetPath):
    for root, dirs, files in os.walk(p_targetPath, topdown=False):
        for file in files:
            file = os.path.join(root, file)
            shutil.copyfileobj(open(file, 'rb'), p_outputFile)

    
def Buildtable(p_outputFile, p_targetPath):
    table_size = 0
    p_outputFile.write(bytes("TABLE_START\n", 'UTF-8'))
    table_size+= 12 #TABLE_START\n
    readpoint = 0
    for root, dirs, files in os.walk(p_targetPath, topdown=False):
        for file in files:
            file = os.path.join(root, file)
            subpath = file.split(p_targetPath+"\\")
            file_size = str(os.path.getsize(file))
            table_size += len(file_size + subpath[1]) +1 # +1 to account for the  \n
            table_size += len(str(readpoint)) +2 #+2 to accunt for :
            p_outputFile.write(bytes(subpath[1]+":", 'UTF-8')+bytes(file_size+":",'UTF-8')+bytes(str(readpoint),'UTF-8')+bytes('\n','UTF-8'))
            readpoint += os.path.getsize(file)
        
    p_outputFile.write(bytes("TABLE_END\n", 'UTF-8'))
    table_size+= 10 #TABLE_END\n
    table_size+= 12 #TABLE_SIZE: + \n
    tablepre = len(str(table_size))
    table_size += tablepre
    while tablepre != len(str(table_size)):#Issue if the size goes from 99 to 100 i.e since 100 is 1byte larger
	    table_size += len(str(table_size))
	    table_size -= tablepre
	    print("Check file size and what the table says, might be an error")
    p_outputFile.write(bytes("TABLE_SIZE:"+str(table_size)+"\n",'UTF-8'))   

def CreateFile():
    path = input("Path to target folder(Note, don't have this script in the same folder): ")
    while not os.path.isdir(path):
       print("Path not found")
       path = input("Path to target folder: ")
    filename = input("Name of concatenated file(.tejp will be automagically appended): ")

    destination = open(filename+".tejp", 'wb')
    Buildtable(destination, path)
    Concatenate(destination, path)
    destination.close()

##UNPACKING FUNCTIONS

def Readtable(p_source):
    table = ()
    read_value = p_source.readline()
    if read_value.decode('UTF-8') != "TABLE_START\n":
        print("Can't find table in file, aborting")
        p_error = 1
        return -1
    while(1):
        file_data = p_source.readline()
        if file_data.decode('UTF-8') == "TABLE_END\n":
            break
        split_string = file_data.decode('UTF-8').split(':')
        table += (split_string[0], split_string[1])
        """
        p_table[split_string[0]] = split_string[1]
        print (split_string[0] )
        print('\n')
        print(p_table)
        print('\n')
        """
    table_size =  p_source.readline().decode('UTF-8').split(':')
    return 0, int(table_size[1]), table
def Constructfiles(p_targetPath, p_source, p_table, p_readPoint):
    for i in range(0,len(p_table),2):
        path = (p_table[i])
        size = (p_table[i+1])
        dir_path = os.path.dirname(os.path.abspath(p_targetPath + "//" + path))
        if not os.path.isdir(dir_path):
            print("creating directory: " + str(dir_path))
            os.makedirs(dir_path)
        new_file = open(p_targetPath + "//" + path, 'wb')
        print(path)
        print("readpoint: " + str(p_readPoint))
        print("size: " +str(size))
        p_source.seek(p_readPoint,0)
        new_file.write(p_source.read(int(size)))
        p_readPoint += int(size)
    return 0    

def UnpackFile():
    filename = input("File to unpack, must have a correct table at beginning of file: ")
    while not os.path.isfile(filename):
        print("File not found")
        filename = input("File to unpack, must have a correct table at beginning of file: ")
    path = input("Path to where files will be unpacked: ")
    if not os.path.isdir(path):
        if len(path) != 0:
            print("makeing directory")
            os.makedirs(path)
        else:
            print("using current directory")
            path = os.getcwd()
    
    source = open(filename, 'rb')
    error = 0
    table_size = 0;
    error , table_size, table = Readtable(source)
    if error != 0:
        return
    error = Constructfiles(path, source, table, table_size)
    if error != 0:
        return
    
#Add this when unpacker is finished, if ever

option = input("Concatenate file or unpack a .tejp file(C or U): ")
if option == 'C' or option == 'c':
    CreateFile()
elif option == 'U' or option == 'u':
    UnpackFile()
else:
    print("Bad input")



