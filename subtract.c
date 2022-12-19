
#include "./imgio.c"
#include <time.h>

int main(argc, argv)
   int  argc;
   char *argv[];
{
clock_t start, end;
double cpu_time_used;


   char     name1[100], name2[100], name3[100];
   long     bits_per_pixel, length, width;
   short    **image1, **image2;
   short    max;

 
   if(argc != 5){
    printf(
     "\n"
     "\n No parameter given at the time of execution >>>>>>>>>"
     "\n recall with parameters file 1, file 2, output file, s=subtract\n");
    exit(0);
   }


   strcpy(name1, argv[0]);
   strcpy(name2, argv[1]);
   strcpy(name3, argv[2]);

   if(does_not_exist(name1)){
    printf("\nERROR input file %s does not exist",
             name1);
    exit(0);
   }

   if(does_not_exist(name2)){
    printf("\nERROR input file %s does not exist",
             name2);
    exit(0);
   }

   if(are_not_same_size(name1, name2)){
      printf(
      "\nERROR Image files %s and %s are not same size",
      name1, name2);
      exit(0);
   }


   get_image_size(name1, &length, &width);
   get_bitsperpixel(name1, &bits_per_pixel);
   image1 = allocate_image_array(length, width);
   image2 = allocate_image_array(length, width);

   create_image_file(name1, name3);
   read_image_array(name1, image1);
   read_image_array(name2, image2);

   if(argv[4][0] == 's' || argv[4][0] == 'S')
  start = clock();
      subtract_image_array(image1, image2,
         length, width);

      
   end = clock();
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   printf("fun() took %f seconds to execute \n", cpu_time_used);

   write_image_array(name3, image2);
   free_image_array(image1, length);
   free_image_array(image2, length);

}  /* ends main  */
