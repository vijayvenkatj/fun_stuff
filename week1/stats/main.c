#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static const char *file_type(mode_t mode) {

  if (S_ISREG(mode)) {
    return "regular file";
  }
  if (S_ISDIR(mode)) {
    return "directory";
  }
  if (S_ISLNK(mode)) {
    return "symbolic link";
  }
  if (S_ISCHR(mode)) {
    return "charecter device";
  }
  if (S_ISBLK(mode)) {
    return "block device";
  }
  if (S_ISFIFO(mode)) {
    return "named pipe";
  }
  if (S_ISSOCK(mode)) {
    return "unix socket";
  }

  return "invalid file type";
}

static void perm_string(mode_t mode, char perm[10]) {
  const char *perms = "rwxrwxrwx";
  mode_t bits = 0400;

  for (int i = 0; i < 9; i++) {
    if ((bits & mode) != 0) {
      perm[i] = perms[i];
    } else {
      perm[i] = '-';
    }

    bits >>= 1;
  }
  perm[9] = '\0';
}

typedef int (*stat_fn) (const char *, struct stat *);

void show(stat_fn statfn, char *file_name) {
  struct stat sb;

  if (statfn(file_name, &sb) == -1) {
    perror(file_name);
    exit(EXIT_FAILURE);
  }

  char perms[10];
  perm_string(sb.st_mode, perms);

  fprintf(stdout, "INODE NO: %ju \n", sb.st_ino);
  fprintf(stdout, "FILE TYPE: %s \n", file_type(sb.st_mode));
  fprintf(stdout, "PERMS: %s (%04o)\n", perms, (unsigned)(sb.st_mode & 0777));
  fprintf(stdout, "SIZE: %jd \n", sb.st_size);
  fprintf(stdout, "LINKS: %d \n", sb.st_nlink);  
}

int main(int argc, char *argv[]) {
   
  int first = 1;
  int use_lstat = 0;
  if (argc > 1 && strcmp(argv[1], "-l") == 0) {
      use_lstat = 1;
      first = 2;
  }

  if (first >= argc) {
      fprintf(stderr, "Usage: %s [-l] FILE...\n", argv[0]);
      exit(EXIT_FAILURE);
  }
  stat_fn statfn = use_lstat ? lstat : stat;

  show(statfn, argv[first]);


  exit(EXIT_SUCCESS);
}
