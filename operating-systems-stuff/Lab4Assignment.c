#include <dirent.h> // for opendir, readdir, closedir
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>  // for struct stat, stat

void traverse_dir(const char *dir_path, FILE *output_file)
{
    // opendir returns pointer to DIR structure that we can use to access
    // dir contents
    DIR *dir;
    struct dirent *entry;
    char path[1024];
    struct stat file_stat;

    // check if result is null if opendir fails
    if (!(dir = opendir(dir_path)))
    {
      perror("opendir");
      return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
      // we want to skip current and parent dir entries
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      {
        continue;
      }

      // we create full path
      snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

      // use stat to get file information
        if (stat(path, &file_stat) == -1) 
        {
            perror("stat");
            continue;
        }

      // if entry is dir, we want to go inside it
      if (S_ISDIR(file_stat.st_mode)) 
      {
          traverse_dir(path, output_file);
      }
      // else wr print file and size
      else if (S_ISREG(file_stat.st_mode)) 
      {
          fprintf(output_file, "File: %s, Size: %ld bytes\n", path, file_stat.st_size); 
      }
    }
   closedir(dir);
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    printf("Usage: %s <dir> <output_file>\n", argv[0]);
    return 1;
  }

  // open output file
  FILE *output_file = fopen(argv[2], "w");
  if (!output_file)
  {
    perror("fopen");
    return 2;
  }

  // traverse dir and write to output file
  traverse_dir(argv[1], output_file);
  
  // close file
  fclose(output_file);
  return 0;
}