"""
Get CPP class and convert to C functions.
This is not supposed to be perfect, its to cover 80%, rest is manual.
"""

def generate_code(prefix, addFirstParam, classCode):
    """
    Generate C wrapper code.
    prefix = methods prefix.
    addFirstParam = if provided, will push as first param (for example: "IntPtr assets")
    classCode = the class code to convert.
    """

    # iterate code lines
    lines = classCode.split('\n')
    prevLine = ""
    comment = ""
    is_private = True
    for i in range(len(lines)):
        
        # get line and previous line
        line = lines[i].strip()
        if i > 0:
            prevLine = lines[i - 1].strip()
        
        # get comments
        if prevLine == "/**" and line.startswith('*'):
            comment = line
            continue

        # public modifier
        if line == "public:":
            is_private = False
            continue
      
        # private modifier
        if line == "private:" or line == "protected:":
            is_private = True
            continue
            
        # skip privates
        if is_private:
            continue
            
        # skip comments
        if line.startswith('*'):
            continue

        # check if a function we should copy
        if '(' in line and ')' in line:
        
            # remove junk
            line = line.replace("virtual", "").replace(" = 0", "").replace(';', '').strip().replace(' (', '(').replace(' )', ')').replace(' *', '*')
            
            # remove inlines
            if '{' in line:
                line = line.split('{')[0].strip()
                
            # remove const modifier
            if ") const" in line:
                line = line.replace(") const", ")")
            
            # find method name
            name = ""
            parts = line.split(' ')
            for part in parts:
                if '(' in part:
                    name = part.split('(')[0].strip()
                    break
            
            # skip internals
            if name.startswith('_'):
                continue
                
            # list of stuff to replace with pointers
            replace_with_ptr = ["ImageAsset", "MusicAsset", "SoundAsset", "FontAsset", "ConfigAsset"]
            for key in replace_with_ptr:
                line = line.replace(key + ' ', key + '* ')
                
            # push first param
            if addFirstParam:
                if '()' in line:
                    line = line.replace(name + '(', name + '(' + addFirstParam)
                else:
                    line = line.replace(name + '(', name + '(' + addFirstParam + ',')
                    
            # set method name
            line = line.replace(' ' + name + '(', ' ' + prefix + name + '(')
            
            # print function
            print ("/**")
            print (comment)
            print ("*/")
            print ('BON_DLLEXPORT ' + line + ';')
            print ("")
        
        # store previous line
        prevLine = line