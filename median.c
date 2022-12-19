
#include "imgio.c"

int does_not_exist();
int create_image_file();
int get_image_size();
int read_image_array();
int free_image_array();
int write_image_array();
int get_bitsperpixel();
int filter_image();
int high_pixel();
int low_pixel();
int median_filter();

int main(argc, argv)
   int argc;
   char *argv[];
{
   char     name1[MAX_NAME_LENGTH];
   char     name2[MAX_NAME_LENGTH];
   char     low_high[MAX_NAME_LENGTH];
   int      i, j, size, type;
   long     bits_per_pixel, length, width;
   short    **the_image, **out_image, filter[3][3];


   if(argc < 5  ||  argc > 6){
    printf(
    "\nusage 1: mfilter in-image out-image g Low-High type"
    "\n                 OR"
    "\nusage 2: mfilter in-image out-image High-Low-Median size"
    "\n                   h - high pixel"
    "\n                   l - low pixel"
    "\n                   m - median pixel"
    "\n                  "
    "\n Using the General type requires entering "
    "\n the type per the following table"
    "\n L -  6"
    "\n L -  9"
    "\n L - 10"
    "\n L - 16"
    "\n L - 32"
    "\n H -  1"
    "\n H -  2"
    "\n H -  3"
    "\n Using the High-Low-Median type requirs entering "
    "\n the size of the filtered area 3 (3x3) 5, 7, 9, etc.\n");
    exit(0);
   }

   strcpy(name1, argv[1]);
   strcpy(name2, argv[2]);

   if(does_not_exist(name1)){
      printf("\nERROR input file %s does not exist",
             name1);
      exit(0);
   }  /* ends if does_not_exist */


   create_image_file(name1, name2);
   get_image_size(name1, &length, &width);
   get_bitsperpixel(name1, &bits_per_pixel);
   the_image = allocate_image_array(length, width);
   out_image = allocate_image_array(length, width);
   read_image_array(name1, the_image);

     /* General filtering case */
   if(argc == 6){
      strcpy(low_high, argv[4]);
      type = atoi(argv[5]);
      filter_image(the_image, out_image,
                   length,
                   width,
                   bits_per_pixel,
                   filter, type, low_high);
   }  /* ends if argc == 6 */


     /* High, Low, and Median filtering cases */
   if(argc == 5){
      strcpy(low_high, argv[3]);
      size = atoi(argv[4]);
      if(low_high[0] == 'h' || low_high[0] == 'H')
         high_pixel(the_image, out_image,
                    length,
                    width,
                    size);
      if(low_high[0] == 'l' || low_high[0] == 'L')
         low_pixel(the_image, out_image,
                   length,
                   width,
                   size);
      if(low_high[0] == 'm' || low_high[0] == 'M')
         median_filter(the_image, out_image,
                       length,
                       width,
                       size);
   }  /* ends if argc == 5 */


   write_image_array(name2, out_image);
   free_image_array(the_image, length);
   free_image_array(out_image, length);

}  /* ends main */





int fix_edges();

short lpf_filter_6[3][3] =
   { {0, 1, 0},
     {1, 2, 1},
     {0, 1, 0}};

short lpf_filter_9[3][3] =
   { {1, 1, 1},
     {1, 1, 1},
     {1, 1, 1}};

short lpf_filter_10[3][3] =
   { {1, 1, 1},
     {1, 2, 1},
     {1, 1, 1}};

short lpf_filter_16[3][3] =
   { {1, 2, 1},
     {2, 4, 2},
     {1, 2, 1}};

short lpf_filter_32[3][3] =
   { {1,  4, 1},
     {4, 12, 4},
     {1,  4, 1}};

short hpf_filter_1[3][3] =
   { { 0, -1,  0},
     {-1,  5, -1},
     { 0, -1,  0}};

short hpf_filter_2[3][3] =
   { {-1, -1, -1},
     {-1,  9, -1},
     {-1, -1, -1}};

short hpf_filter_3[3][3] =
   { { 1, -2,  1},
     {-2,  5, -2},
     { 1, -2,  1}};



     int fswap(a, b)
        short *a, *b;
     {
        short temp;
        temp  = *a;
        *a    = *b;
        *b    = temp;
     return(1);
     }  /* ends swap */


     int fsort_elements(elements, count)
        int   *count;
        short elements[];
     {
        int i, j;
        j = *count;
        while(j-- > 1){
           for(i=0; i<j; i++){
              if(elements[i] > elements[i+1])
                 fswap(&elements[i], &elements[i+1]);
           }
        }

     return(1);
     }  /* ends fsort_elements */



     int median_of(elements, count)
        int   *count;
        short elements[];
     {
        short median;

        fsort_elements(elements, count);
        median = elements[*count/2];
        return(median);
     }  /* ends median_of */


     int setup_filters(filter_type, low_high, filter)
        char   low_high[];
        int    filter_type;
        short  filter[3][3];
     {
        int i, j;

        if(low_high[0] == 'l'  || low_high[0] =='L'){
           if(filter_type == 6){
              for(i=0; i<3; i++){
                for(j=0; j<3; j++){
                  filter[i][j] = lpf_filter_6[i][j];
                }
              }
           }  /* ends if filter_type == 6 */

           if(filter_type == 9){
              for(i=0; i<3; i++){
                for(j=0; j<3; j++){
                  filter[i][j] = lpf_filter_9[i][j];
                }
              }
           }  /* ends if filter_type == 9 */

           if(filter_type == 10){
              for(i=0; i<3; i++){
                for(j=0; j<3; j++){
                  filter[i][j] = lpf_filter_10[i][j];
                }
              }
           }  /* ends if filter_type == 10 */


           if(filter_type == 16){
              for(i=0; i<3; i++){
                for(j=0; j<3; j++){
                  filter[i][j] = lpf_filter_16[i][j];
                }
              }
           }  /* ends if filter_type == 16 */


           if(filter_type == 32){
              for(i=0; i<3; i++){
                for(j=0; j<3; j++){
                  filter[i][j] = lpf_filter_32[i][j];
                }
              }
           }  /* ends if filter_type == 32 */
        }  /* ends low pass filter */




        if(low_high[0] == 'h'  || low_high[0] =='H'){
           if(filter_type == 1){
              for(i=0; i<3; i++){
                for(j=0; j<3; j++){
                  filter[i][j] = hpf_filter_1[i][j];
                }
              }
           }  /* ends if filter_type == 1 */

           if(filter_type == 2){
              for(i=0; i<3; i++){
                for(j=0; j<3; j++){
                  filter[i][j] = hpf_filter_2[i][j];
                }
              }
           }  /* ends if filter_type == 2 */

           if(filter_type == 3){
              for(i=0; i<3; i++){
                for(j=0; j<3; j++){
                  filter[i][j] = hpf_filter_3[i][j];
                }
              }
           }  /* ends if filter_type == 3 */
        }  /* ends high pass filter */

     return(1);
     }  /* ends setup_filters */




int filter_image(the_image, out_image,
             rows, cols, bits_per_pixel,
             filter, type, low_high)
   int    type;
   short  filter[3][3],
          **the_image,
          **out_image;
   char   low_high[];
   long   rows, cols, bits_per_pixel;

{
   int    a, b, d, i, j, k,
          length, max, sum, width;

   setup_filters(type, low_high, filter);

   d = type;
   if(type == 2 || type == 3) d = 1;

   max = 255;
   if(bits_per_pixel == 4)
      max = 16;

         /* Do convolution over image array */
   printf("\n");
   for(i=1; i<rows-1; i++){
      if( (i%10) == 0) printf("%d ", i);
      for(j=1; j<cols-1; j++){
         sum = 0;
         for(a=-1; a<2; a++){
            for(b=-1; b<2; b++){
               sum = sum +
                     the_image[i+a][j+b] *
                     filter[a+1][b+1];
            }
         }
         sum               = sum/d;
         if(sum < 0)   sum = 0;
         if(sum > max) sum = max;
         out_image[i][j]   = sum;

      }  /* ends loop over j */
   }  /* ends loop over i */
   fix_edges(out_image, 1, rows-1, cols-1);

return(1);
}  /* ends filter_image */



int median_filter(the_image, out_image,
              rows, cols, size)
   int    size;
   short  **the_image,
          **out_image;
   long   rows, cols;

{
   int    a, b, count, i, j, k,
          length, sd2, sd2p1, ss, width;
   short  *elements;

   sd2   = size/2;
   sd2p1 = sd2 + 1;

   ss       = size*size;
   elements = (short *) malloc(ss * sizeof(short));


   printf("\n");
   for(i=sd2; i<rows-sd2; i++){
      if( (i%10) == 0) printf("%d ", i);
      for(j=sd2; j<cols-sd2; j++){
         count = 0;
         for(a=-sd2; a<sd2p1; a++){
            for(b=-sd2; b<sd2p1; b++){
               elements[count] = the_image[i+a][j+b];
               count++;
            }
         }
         out_image[i][j] = median_of(elements, &ss);
      }  /* ends loop over j */
   }  /* ends loop over i */

   free(elements);
   fix_edges(out_image, sd2, rows-1, cols-1);

return(1);
}  /* ends median_filter */




int low_pixel(the_image, out_image,
          rows, cols, size)
   int    size;
   short  **the_image,
          **out_image;
   long   rows, cols;

{
   int    a, b, count, i, j, k,
          length, sd2, sd2p1, ss, width;
   short  *elements;

   sd2   = size/2;
   sd2p1 = sd2 + 1;

   ss       = size*size;
   elements = (short *) malloc(ss * sizeof(short));



   printf("\n");
   for(i=sd2; i<rows-sd2; i++){
      if( (i%10) == 0) printf("%d ", i);
      for(j=sd2; j<cols-sd2; j++){
         count = 0;
         for(a=-sd2; a<sd2p1; a++){
            for(b=-sd2; b<sd2p1; b++){
               elements[count] = the_image[i+a][j+b];
               count++;
            }
         }
         fsort_elements(elements, &ss);
         out_image[i][j] = elements[0];
      }  /* ends loop over j */
   }  /* ends loop over i */

   free(elements);
   fix_edges(out_image, sd2, rows-1, cols-1);

return(1);
}  /* ends low_pixel */




int high_pixel(the_image, out_image,
           rows, cols, size)
   int    size;
   short  **the_image,
          **out_image;
   long   rows, cols;
{
   int    a, b, count, i, j, k,
          length, sd2, sd2p1, ss, width;
   short  *elements;

   sd2   = size/2;
   sd2p1 = sd2 + 1;



   ss       = size*size;
   elements = (short *) malloc(ss * sizeof(short));

   printf("\n");
   for(i=sd2; i<rows-sd2; i++){
      if( (i%10) == 0) printf("%d ", i);
      for(j=sd2; j<cols-sd2; j++){
         count = 0;
         for(a=-sd2; a<sd2p1; a++){
            for(b=-sd2; b<sd2p1; b++){
               elements[count] = the_image[i+a][j+b];
               count++;
            }
         }
         fsort_elements(elements, &ss);
         out_image[i][j] = elements[ss-1];
      }  /* ends loop over j */
   }  /* ends loop over i */

   free(elements);
   fix_edges(out_image, sd2, rows-1, cols-1);

return(1);
}  /* ends high_pixel */


int swap();


int fix_edges(im, w, rows, cols)
      int   w;
      short **im;
      long  rows, cols;
{
   int i, j;

printf("\nFIX> rows=%ld cols=%ld w=%d",rows,cols,w);
      /* four corners */
   for(i=w; i>0; i--){
    im[i-1][i-1] = im[i][i];
    im[i-1][cols-(i-1)] = im[i][cols-1-(i-1)];
    im[rows-(i-1)][i-1] = im[rows-1-(i-1)][i];
    im[rows-(i-1)][cols-(i-1)] = im[rows-1-(i-1)][cols-1-(i-1)];
   }  /* ends four corners loop */

   for(i=0; i<rows; i++){
      for(j=w; j>0; j--){
       im[i][j-1] = im[i][j];
       im[i][cols-j] = im[i][cols-j-1];
      }
   }

   for(j=0; j<cols; j++){
      for(i=w; i>0; i--){
       im[i-1][j] = im[i][j];
       im[rows-i][j] = im[rows-i-1][j];
      }
   }
return(1);
}  /* ends fix_edges */