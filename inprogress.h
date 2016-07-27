http://stackoverflow.com/questions/18100097/portable-way-to-check-if-directory-exists-windows-linux-c
#include <sys/types.h>
#include <sys/stat.h>

struct stat info;

if( stat( pathname, &info ) != 0 )
    printf( "cannot access %s\n", pathname );
else if( info.st_mode & S_IFDIR )  // S_ISDIR() doesn't exist on my windows 
    printf( "%s is a directory\n", pathname );
else
    printf( "%s is no directory\n", pathname );



http://stackoverflow.com/questions/734717/how-to-delete-a-folder-in-c

void remove_dir(char *path)
{
        struct dirent *entry = NULL;
        DIR *dir = NULL;
        dir = opendir(path);
        while(entry = readdir(dir))
        {   
                DIR *sub_dir = NULL;
                FILE *file = NULL;
                char abs_path[100] = {0};
                if(*(entry->d_name) != '.')
                {   
                        sprintf(abs_path, "%s/%s", path, entry->d_name);
                        if(sub_dir = opendir(abs_path))
                        {   
                                closedir(sub_dir);
                                remove_dir(abs_path);
                        }   
                        else 
                        {   
                                if(file = fopen(abs_path, "r"))
                                {   
                                        fclose(file);
                                        remove(abs_path);
                                }   
                        }   
                }   
        }   
        remove(path);
}


