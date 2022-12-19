
#include "cips.h"


int does_not_exist(file_name)
    char file_name[];
{
   FILE *image_file;
   int  result;

   result = 1;
   image_file = fopen(file_name, "rb");
   if(image_file != NULL){
      result = 0;
      fclose(image_file);
   }
   return(result);
}  /* ends does_not_exist */



int insert_short_into_buffer(buffer, start, number)
    char  buffer[];
    int   start;
    short number;
{
    union short_char_union lsu;

    lsu.s_num       = number;
    buffer[start+0] = lsu.s_alpha[0];
    buffer[start+1] = lsu.s_alpha[1];

   return(1);
}  /* ends insert_short_into_buffer */


int insert_ushort_into_buffer(buffer, start, number)
    char  buffer[];
    int   start;
    unsigned short number;
{
    union ushort_char_union lsu;

    lsu.s_num       = number;
    buffer[start+0] = lsu.s_alpha[0];
    buffer[start+1] = lsu.s_alpha[1];

   return(1);
}  /* ends insert_short_into_buffer */




int insert_long_into_buffer(buffer, start, number)
    char buffer[];
    int  start;
    long number;
{
    union long_char_union lsu;

    lsu.l_num       = number;
    buffer[start+0] = lsu.l_alpha[0];
    buffer[start+1] = lsu.l_alpha[1];
    buffer[start+2] = lsu.l_alpha[2];
    buffer[start+3] = lsu.l_alpha[3];

   return(1);
}  /* ends insert_short_into_buffer */



int insert_ulong_into_buffer(buffer, start, number)
    char buffer[];
    int  start;
    unsigned long number;
{
    union ulong_char_union lsu;

    lsu.l_num       = number;
    buffer[start+0] = lsu.l_alpha[0];
    buffer[start+1] = lsu.l_alpha[1];
    buffer[start+2] = lsu.l_alpha[2];
    buffer[start+3] = lsu.l_alpha[3];

   return(1);
}  /* ends insert_ulong_into_buffer */


int extract_long_from_buffer(buffer, lsb, start, number)
   char  buffer[];
   int       lsb, start;
   long  *number;
{
   int i;
   union long_char_union lcu;

   lcu.l_num = 0; /*****HERE*****/


   if(lsb == 1){
      lcu.l_alpha[0] = buffer[start+0];
      lcu.l_alpha[1] = buffer[start+1];
      lcu.l_alpha[2] = buffer[start+2];
      lcu.l_alpha[3] = buffer[start+3];
   }  /* ends if lsb = 1 */

   if(lsb == 0){
      lcu.l_alpha[0] = buffer[start+3];
      lcu.l_alpha[1] = buffer[start+2];
      lcu.l_alpha[2] = buffer[start+1];
      lcu.l_alpha[3] = buffer[start+0];
   }  /* ends if lsb = 0      */

   *number = lcu.l_num;

   return(1);

}  /* ends extract_long_from_buffer */



int extract_ulong_from_buffer(buffer, lsb, start, number)
   char  buffer[];
   int       lsb, start;
   unsigned long  *number;
{
   int i;
   union ulong_char_union lcu;

   lcu.l_num = 0;

   if(lsb == 1){
      lcu.l_alpha[0] = buffer[start+0];
      lcu.l_alpha[1] = buffer[start+1];
      lcu.l_alpha[2] = buffer[start+2];
      lcu.l_alpha[3] = buffer[start+3];
   }  /* ends if lsb = 1 */

   if(lsb == 0){
      lcu.l_alpha[0] = buffer[start+3];
      lcu.l_alpha[1] = buffer[start+2];
      lcu.l_alpha[2] = buffer[start+1];
      lcu.l_alpha[3] = buffer[start+0];
   }  /* ends if lsb = 0      */

   *number = lcu.l_num;
   return(1);
}  /* ends extract_ulong_from_buffer */



int extract_short_from_buffer(buffer, lsb, start, number)
   char  buffer[];
   int   lsb, start;
   short *number;
{

   int i;
   union short_char_union lcu;

   lcu.s_num = 0;

   if(lsb == 1){
      lcu.s_alpha[0] = buffer[start+0];
      lcu.s_alpha[1] = buffer[start+1];
   }  /* ends if lsb = 1 */

   if(lsb == 0){
      lcu.s_alpha[0] = buffer[start+1];
      lcu.s_alpha[1] = buffer[start+0];
   }  /* ends if lsb = 0      */

   *number = lcu.s_num;
   return(1);

}  /* ends extract_short_from_buffer */



int extract_ushort_from_buffer(buffer, lsb, start, number)
   char  buffer[];
   int       lsb, start;
   unsigned short *number;
{

   int i;
   union ushort_char_union lcu;

   lcu.s_num = 0;

   if(lsb == 1){
      lcu.s_alpha[0] = buffer[start+0];
      lcu.s_alpha[1] = buffer[start+1];
   }  /* ends if lsb = 1 */

   if(lsb == 0){
      lcu.s_alpha[0] = buffer[start+1];
      lcu.s_alpha[1] = buffer[start+0];
   }  /* ends if lsb = 0      */

   *number = lcu.s_num;
   return(1);
}  /* ends extract_ushort_from_buffer */



int print_tiff_header(header)
   struct tiff_header_struct header;
{
   printf("\n");
   printf("\nlsb: %d", header.lsb);
   printf("\nbits per pixel: %ld", header.bits_per_pixel);
   printf("\nimage length: %ld", header.image_length);
   printf("\nimage width: %ld", header.image_width);
   printf("\nstrip offset: %ld", header.strip_offset);
   printf("\n");
   return(1);
} /* ends print_tiff_header */



int read_bmp_file_header(file_name,
                     file_header)
   char *file_name;
   struct bmpfileheader *file_header;
{
   char  buffer[10];
   long  ll;
   short ss;
   unsigned long  ull;
   unsigned short uss;
   FILE     *fp;

   fp = fopen(file_name, "rb");

   fread(buffer, 1, 2, fp);
   extract_ushort_from_buffer(buffer, 1, 0, &uss);
   file_header->filetype = uss;

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   file_header->filesize = ull;

   fread(buffer, 1, 2, fp);
   extract_short_from_buffer(buffer, 1, 0, &ss);
   file_header->reserved1 = ss;

   fread(buffer, 1, 2, fp);
   extract_short_from_buffer(buffer, 1, 0, &ss);
   file_header->reserved2 = ss;

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   file_header->bitmapoffset = ull;

   fclose(fp);
   return(1);
}  /* ends read_bmp_file_header */



int calculate_pad(width)
   long width;
{
   int pad = 0;
   pad = ( (width%4) == 0) ? 0 : (4-(width%4));
   return(pad);
}  /* ends calculate_pad */


int is_a_bmp(file_name)
   char *file_name;
{
   char   *cc;
   int    result = 0;
   struct bmpfileheader file_header;

   cc = strstr(file_name, ".bmp");
   if(cc == NULL)
      return(result);

   read_bmp_file_header(file_name, &file_header);
   if(file_header.filetype != 0x4d42)
      return(result);

   result = 1;
   return(result);
}  /* ends is_a_bmp */



int is_a_tiff(file_name)
   char *file_name;
{
   char   *cc;
   char   buffer[4];
   FILE   *fp;
   int    ok     = 0,
          result = 0;

   cc = strstr(file_name, ".tif");
   if(cc == NULL)
      return(result);

   fp = fopen(file_name, "rb");
   fread(buffer, 1, 4, fp);
   fclose(fp);

   if(buffer[0] == 0x49  &&
      buffer[1] == 0x49  &&
      buffer[2] == 0x2a  &&
      buffer[3] == 0x00)
      ok = 1;

   if(buffer[0] == 0x4d  &&
      buffer[1] == 0x4d  &&
      buffer[2] == 0x00  &&
      buffer[3] == 0x2a)
      ok = 1;

   if(ok == 0)
      return(result);

   result = 1;
   return(result);
}  /* ends is_a_tiff */



int read_tiff_header(file_name, image_header)
   char file_name[];
   struct tiff_header_struct *image_header;
{
   char buffer[12], response[80];

   FILE *image_file;

   int  bytes_read,
        closed,
        i,
        j,
        lsb,
        not_finished,
        position;

   long bits_per_pixel,
        image_length,
        image_width,
        offset_to_ifd,
        strip_offset,
        subfile,
        value;

   short entry_count,
         field_type,
         length_of_field,
         s_bits_per_pixel,
         s_image_length,
         s_image_width,
         s_strip_offset,
         tag_type;

   image_file = fopen(file_name, "rb");
   if(image_file != NULL){



   bytes_read = fread(buffer, 1, 8, image_file);

   if(buffer[0] == 0x49)
      lsb = 1;
   else
      lsb = 0;



   extract_long_from_buffer(buffer, lsb, 4,
                            &offset_to_ifd);

   not_finished = 1;
   while(not_finished){



      position   = fseek(image_file, offset_to_ifd,
                         SEEK_SET);
      bytes_read = fread(buffer, 1, 2, image_file);
      extract_short_from_buffer(buffer, lsb, 0,
                                &entry_count);

 
        for(i=0; i<entry_count; i++){
       bytes_read = fread(buffer, 1, 12, image_file);
       extract_short_from_buffer(buffer, lsb, 0,
                                 &tag_type);

       switch(tag_type){

          case 255: /* Subfile Type */
             extract_short_from_buffer(buffer, lsb, 2,
                                       &field_type);
             extract_short_from_buffer(buffer, lsb, 4,
                                    &length_of_field);
             extract_long_from_buffer(buffer, lsb, 8,
                                      &subfile);
             break;

          case 256: /* ImageWidth */
             extract_short_from_buffer(buffer, lsb, 2,
                                       &field_type);
             extract_short_from_buffer(buffer, lsb, 4,
                                    &length_of_field);
             if(field_type == 3){
              extract_short_from_buffer(buffer, lsb, 8,
                                     &s_image_width);
              image_width = s_image_width;
             }
             else
              extract_long_from_buffer(buffer, lsb, 8,
                                       &image_width);
             break;

          case 257: /* ImageLength */
             extract_short_from_buffer(buffer, lsb, 2,
                                       &field_type);
             extract_short_from_buffer(buffer, lsb, 4,
                                    &length_of_field);
             if(field_type == 3){
              extract_short_from_buffer(buffer, lsb, 8,
                                    &s_image_length);
              image_length = s_image_length;
             }
             else
              extract_long_from_buffer(buffer, lsb, 8,
                                       &image_length);
             break;

          case 258: /* BitsPerSample */
             extract_short_from_buffer(buffer, lsb, 2,
                                       &field_type);
             extract_short_from_buffer(buffer, lsb, 4,
                                    &length_of_field);
             if(field_type == 3){
              extract_short_from_buffer(buffer, lsb, 8,
                                   &s_bits_per_pixel);
              bits_per_pixel = s_bits_per_pixel;
             }
             else
              extract_long_from_buffer(buffer, lsb, 8,
                                    &bits_per_pixel);
             break;

          case 273: /* StripOffset */
             extract_short_from_buffer(buffer, lsb, 2,
                                       &field_type);
             extract_short_from_buffer(buffer, lsb, 4,
                                    &length_of_field);
             if(field_type == 3){
              extract_short_from_buffer(buffer, lsb, 8,
                                    &s_strip_offset);
              strip_offset = s_strip_offset;
             }
             else
              extract_long_from_buffer(buffer, lsb, 8,
                                       &strip_offset);
             break;

          default:
             break;

       }  /* ends switch tag_type */

      }  /* ends loop over i directory entries */

      bytes_read = fread(buffer, 1, 4, image_file);
      extract_long_from_buffer(buffer, lsb, 0,
                               &offset_to_ifd);
      if(offset_to_ifd == 0) not_finished = 0;

   }  /* ends while not_finished */


   image_header->lsb                = lsb;
   image_header->bits_per_pixel     = bits_per_pixel;
   image_header->image_length       = image_length;
   image_header->image_width        = image_width;
   image_header->strip_offset       = strip_offset;

   closed = fclose(image_file);
   }  /* ends if file opened ok */
   else{
      printf("\n\nTIFF.C> ERROR - could not open "
             "tiff file");
      return(0);
   }
   return(1);
}  /* ends read_tiff_header */




short** allocate_image_array(length, width)
   long  length, width;
{
   int i, j;

   short** the_array = (short**) malloc(length * sizeof(short*));
   for(i=0; i<length; i++){
      the_array[i] = (short*) malloc(width * sizeof(short));
      if(the_array[i] == NULL){
         printf("\n\tmalloc of the_image[%d] failed", i);
      }  /* ends if */
   }  /* ends loop over i */

   for(i=0; i<length; i++)
      for(j=0; j<width; j++)
         the_array[i][j] = 0;

   return(the_array);

}  /* ends allocate_image_array */



int free_image_array(the_array, length)
   short **the_array;
   long  length;
{
   int i;
   for(i=0; i<length; i++)
      free(the_array[i]);
   free(the_array);  /***** HERE ****/
   return(1);
}  /* ends free_image_array */




int read_line(image_file, the_image, line_number,
          image_header, ie, le)
   FILE   *image_file;
   int    ie, le, line_number;
   short  **the_image;
   struct tiff_header_struct *image_header;
{
   char  *buffer, first, second;
   float a, b;
   int bytes_read, i;
   unsigned int bytes_to_read;
   union short_char_union scu;



   buffer = (char  *) malloc(image_header->image_width * sizeof(char ));
   for(i=0; i<image_header->image_width; i++)
      buffer[i] = '\0';


   bytes_to_read = (le-ie)/
                   (8/image_header->bits_per_pixel);
   bytes_read    = fread(buffer, 1, bytes_to_read,
                         image_file);

   for(i=0; i<bytes_read; i++){


      if(image_header->bits_per_pixel == 8){
       scu.s_num                 = 0;
       scu.s_alpha[0]            = buffer[i];
       the_image[line_number][i] = scu.s_num;
      }  /* ends if bits_per_pixel == 8 */

      if(image_header->bits_per_pixel == 4){

       scu.s_num             = 0;
       second                = buffer[i] & 0X000F;
       scu.s_alpha[0]        = second;
       the_image[line_number][i*2+1] = scu.s_num;

       scu.s_num             = 0;
       first                 = buffer[i] >> 4;
       first                 = first & 0x000F;
       scu.s_alpha[0]        = first;
       the_image[line_number][i*2] = scu.s_num;

      }  /* ends if bits_per_pixel == 4 */

   }  /*  ends loop over i  */

   free(buffer);
   return(bytes_read);

   return(1);
}  /* ends read_line  */



int read_tiff_image(image_file_name, the_image)
      char   image_file_name[];
      short   **the_image;
{
   char  *buffer,  /* CHANGED */
         rep[80];
   int   bytes_read,
         closed,
         position,
         i,
         j;
   FILE  *image_file;
   float a;
   long  line_length, offset;

   struct tiff_header_struct image_header;

   read_tiff_header(image_file_name, &image_header);


   image_file = fopen(image_file_name, "rb");
   if(image_file != NULL){
      position = fseek(image_file,
                       image_header.strip_offset,
                       SEEK_SET);

      for(i=0; i<image_header.image_length; i++){

         bytes_read   = read_line(image_file, the_image,
                                  i, &image_header,
                                  0, image_header.image_width);
      }  /* ends loop over i  */

      closed = fclose(image_file);
   }  /* ends if file opened ok */
   else{
      printf("\nRTIFF.C> ERROR - cannot open "
             "tiff file");
   }

   return(1);
}  /*  ends read_tiff_image */



int seek_to_first_line(image_file, image_header, il)
   FILE   *image_file;
   int    il;
   struct tiff_header_struct *image_header;
{
   long offset;
   int  position;

   offset   = (il-1)*image_header->image_width/
             (8/image_header->bits_per_pixel);
      /* seek from current position */
   position = fseek(image_file, offset, SEEK_CUR);
   return(position);
}  /* ends seek_to_first_line */




int seek_to_end_of_line(image_file, le, image_header)
   FILE   *image_file;
   int    le;
   struct tiff_header_struct *image_header;
{
   long  offset;
   int   position;

   offset   = (image_header->image_width-le)/
             (8/image_header->bits_per_pixel);
   position = fseek(image_file, offset, SEEK_CUR);
   return(position);
}  /* ends seek_to_end_of_line         */




int create_allocate_tiff_file(file_name,
                          image_header)
   char   file_name[];
   struct tiff_header_struct *image_header;
{
   char  buffer[12], *image_buffer, long_buffer[50];
   FILE  *image_file;
   int   bytes_written,
         i,
         j,
         l,
         w;

   long  k;



   image_file = fopen(file_name, "wb");



   buffer[0] = 0x49;
   buffer[1] = 0x49;
   buffer[2] = 0x2A;
   buffer[3] = 0x00;
   buffer[4] = 0x08;
   buffer[5] = 0x00;
   buffer[6] = 0x00;
   buffer[7] = 0x00;

   bytes_written = fwrite(buffer, 1, 8, image_file);

   printf("\n wrote %d bytes", bytes_written);



   buffer[0] = 0x12;
   buffer[1] = 0x00;
   bytes_written = fwrite(buffer, 1, 2, image_file);

   printf("\n wrote %d bytes", bytes_written);

      /* New Subfile Type */
   buffer[0]  = 0xFE;
   buffer[1]  = 0x00;
   buffer[2]  = 0x03;
   buffer[3]  = 0x00;
   buffer[4]  = 0x01;
   buffer[5]  = 0x00;
   buffer[6]  = 0x00;
   buffer[7]  = 0x00;
   buffer[8]  = 0x00;
   buffer[9]  = 0x00;
   buffer[10] = 0x00;
   buffer[11] = 0x00;
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* Subfile Type */
   buffer[0]  = 0xFF;
   buffer[1]  = 0x00;
   buffer[2]  = 0x03;
   buffer[3]  = 0x00;
   buffer[4]  = 0x01;
   buffer[5]  = 0x00;
   buffer[6]  = 0x00;
   buffer[7]  = 0x00;
   buffer[8]  = 0x01;
   buffer[9]  = 0x00;
   buffer[10] = 0x00;
   buffer[11] = 0x00;
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* Image Width */
   insert_short_into_buffer(buffer, 0, 256);
   insert_short_into_buffer(buffer, 2, 3);
   insert_short_into_buffer(buffer, 4, 1);
   insert_short_into_buffer(buffer, 8,
                     image_header->image_width);
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* Image Length */
   insert_short_into_buffer(buffer, 0, 257);
   insert_short_into_buffer(buffer, 2, 3);
   insert_short_into_buffer(buffer, 4, 1);
   insert_short_into_buffer(buffer, 8,
                     image_header->image_length);
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* Bits Per Sample */
   insert_short_into_buffer(buffer, 0, 258);
   insert_short_into_buffer(buffer, 2, 3);
   insert_short_into_buffer(buffer, 4, 1);
   insert_short_into_buffer(buffer, 8,
                     image_header->bits_per_pixel);
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* Compression - None */
   insert_short_into_buffer(buffer, 0, 259);
   insert_short_into_buffer(buffer, 2, 3);
   insert_short_into_buffer(buffer, 4, 1);
   insert_short_into_buffer(buffer, 8, 1);
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* Photometric Interpretation */
      /* set to 1 because BLACK is ZERO */
   insert_short_into_buffer(buffer, 0, 262);
   insert_short_into_buffer(buffer, 2, 3);
   insert_short_into_buffer(buffer, 4, 1);
   insert_short_into_buffer(buffer, 8, 1);
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* Strip Offset */
      /* start after software name at 296 */
   insert_short_into_buffer(buffer, 0, 273);
   insert_short_into_buffer(buffer, 2, 3);
   insert_short_into_buffer(buffer, 4, 1);
   insert_short_into_buffer(buffer, 8, 296);
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* Samples per Pixel */
   insert_short_into_buffer(buffer, 0, 277);
   insert_short_into_buffer(buffer, 2, 3);
   insert_short_into_buffer(buffer, 4, 1);
   insert_short_into_buffer(buffer, 8, 1);
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* clear buffer */
   for(i=0; i<12; i++) buffer[i] = 0x00;

      /* Rows Per Strip 1 strip for the entire image */
      /* use 2E32 - 1, which is max */
   insert_short_into_buffer(buffer, 0, 278);
   insert_short_into_buffer(buffer, 2, 4);
   insert_short_into_buffer(buffer, 4, 1);
   insert_long_into_buffer(buffer, 8, 4294967295);
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* Strip Byte Counts */
      /* this = image width times length */
   insert_short_into_buffer(buffer, 0, 279);
   insert_short_into_buffer(buffer, 2, 4);
   insert_short_into_buffer(buffer, 4, 1);
   insert_long_into_buffer(buffer, 8,
    (long)(image_header->image_length *
           image_header->image_width));
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* Min Sample Value */
   insert_short_into_buffer(buffer, 0, 280);
   insert_short_into_buffer(buffer, 2, 3);
   insert_short_into_buffer(buffer, 4, 1);
   insert_short_into_buffer(buffer, 8, 0);
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* Max Sample Value */
   insert_short_into_buffer(buffer, 0, 281);
   insert_short_into_buffer(buffer, 2, 3);
   insert_short_into_buffer(buffer, 4, 1);
   if(image_header->bits_per_pixel == 8)
      insert_short_into_buffer(buffer, 8, 255);
   else
      insert_short_into_buffer(buffer, 8, 15);
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* X Resolution */
      /* Store the 8 bytes for this value
         starting at 230 */
   insert_short_into_buffer(buffer, 0, 282);
   insert_short_into_buffer(buffer, 2, 5);
   insert_short_into_buffer(buffer, 4, 1);
   insert_short_into_buffer(buffer, 8, 230);
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* Y Resolution */
      /* Store the 8 bytes for this value
         starting at 238 */
   insert_short_into_buffer(buffer, 0, 283);
   insert_short_into_buffer(buffer, 2, 5);
   insert_short_into_buffer(buffer, 4, 1);
   insert_short_into_buffer(buffer, 8, 238);
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);



      /* clear buffer */
   for(i=0; i<12; i++) buffer[i] = 0x00;

      /* Planer Configuration */
      /* chunky */
   insert_short_into_buffer(buffer, 0, 284);
   insert_short_into_buffer(buffer, 2, 3);
   insert_short_into_buffer(buffer, 4, 1);
   insert_short_into_buffer(buffer, 8, 1);
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* Resolution Unit */
      /* inches */
   insert_short_into_buffer(buffer, 0, 296);
   insert_short_into_buffer(buffer, 2, 3);
   insert_short_into_buffer(buffer, 4, 1);
   insert_short_into_buffer(buffer, 8, 2);
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* Software */
      /* Put this a 246, 50 bytes */
   insert_short_into_buffer(buffer, 0, 305);
   insert_short_into_buffer(buffer, 2, 2);
   insert_short_into_buffer(buffer, 4, 50);
   insert_short_into_buffer(buffer, 8, 246);
   bytes_written = fwrite(buffer, 1, 12, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* Offset to next IFD (0 means no more IFD's) */
   for(i=0; i<12; i++) buffer[i] = 0x00;
   bytes_written = fwrite(buffer, 1, 4, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* clear buffer */
   for(i=0; i<12; i++) buffer[i] = 0x00;

      /* Now store the X Resolution
         first long is numerator
         second long is denominator */
   insert_long_into_buffer(buffer, 0, 300L);
   insert_long_into_buffer(buffer, 4, 1L);
   bytes_written = fwrite(buffer, 1, 8, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* Now store the Y Resolution
         first long is numerator
         second long is denominator */
   insert_long_into_buffer(buffer, 0, 300L);
   insert_long_into_buffer(buffer, 4, 1L);
   bytes_written = fwrite(buffer, 1, 8, image_file);
   printf("\n wrote %d bytes", bytes_written);


      /* Now store the software tag */
   for(i=0; i<50; i++) long_buffer[i] = '\0';
   strcpy(long_buffer,
   "Dwayne Phillips C Image Processing System 1993");
   long_buffer[46] = '\0';
   long_buffer[47] = '\0';
   long_buffer[48] = '\0';
   long_buffer[49] = '\0';
   bytes_written = fwrite(long_buffer, 1, 50,
                          image_file);
   printf("\n wrote %d bytes", bytes_written);
   printf("\n%s", long_buffer);


   printf("\n length is %ld",
          image_header->image_length);
   printf("\n width is %ld",
          image_header->image_width);

   k = image_header->image_width;

   if(image_header->bits_per_pixel == 4)
      k = k/2;

   image_buffer = (char  *) malloc(k * sizeof(char ));

   for(i=0; i<k; i++)
      image_buffer[i] = 0x00;

   for(i=0; i<image_header->image_length; i++){
      bytes_written = fwrite(image_buffer, 1, k, image_file);
      /***printf("\n wrote %d bytes", bytes_written);***/
   }

   fclose(image_file);
   free(image_buffer);

   return(1);
}  /* ends create_allocate_tiff_file */



int create_tiff_file_if_needed(in_name, out_name, out_image)
   char in_name[], out_name[];
   short **out_image;
{
   int    length, width;
   struct tiff_header_struct image_header;

   if(does_not_exist(out_name)){
      printf("\n\n output file does not exist %s",
               out_name);
      read_tiff_header(in_name, &image_header);
      create_allocate_tiff_file(out_name, &image_header);
      printf("\nBFIN> Created %s", out_name);
   }  /* ends if does_not_exist */
   return(1);
}  /* ends create_tiff_file_if_needed */



int write_line(image_file, array, line_number,
           image_header, ie, le)
   FILE   *image_file;
   int    ie, le, line_number;
   short  **array;
   struct tiff_header_struct *image_header;
{
   char     *buffer, first, second;
   float    a, b;
   int      bytes_written, i;
   unsigned int bytes_to_write;
   union    short_char_union scu;

   buffer = (char  *) malloc(image_header->image_width * sizeof(char ));
   for(i=0; i<image_header->image_width; i++)
      buffer[i] = '\0';

   bytes_to_write = (le-ie)/
                    (8/image_header->bits_per_pixel);

   for(i=0; i<bytes_to_write; i++){



      if(image_header->bits_per_pixel == 8){
       scu.s_num = 0;
       scu.s_num = array[line_number][i];
       buffer[i] = scu.s_alpha[0];
      }  /* ends if bits_per_pixel == 8 */


      if(image_header->bits_per_pixel == 4){

       scu.s_num = 0;
       scu.s_num = array[line_number][i*2];
       first     = scu.s_alpha[0] << 4;

       scu.s_num = 0;
       scu.s_num = array[line_number][i*2];
       second    = scu.s_alpha[0] & 0X000F;

       buffer[i] = first | second;
      }  /* ends if bits_per_pixel == 4 */

   }  /*  ends loop over i  */


   bytes_written = fwrite(buffer, 1, bytes_to_write,
                          image_file);

   free(buffer);
   return(bytes_written);

}  /* ends write_line  */



int write_tiff_image(image_file_name, array)

        char    image_file_name[];
        short   **array;
{

   FILE  *image_file;
   int   bytes_written,
         closed,
         i,
          position,
         written;

   float a;

   long  line_length,
         offset;

   struct tiff_header_struct image_header;

   read_tiff_header(image_file_name, &image_header);


   image_file = fopen(image_file_name, "rb+");
   position   = fseek(image_file,
                      image_header.strip_offset,
                      SEEK_SET);

   for(i=0; i<image_header.image_length; i++){
      bytes_written = write_line(image_file, array,
                                  i, &image_header,
                                  0, image_header.image_width);
   }  /* ends loop over i  */

   closed = fclose(image_file);
   return(1);
}  /*  ends write_tiff_image */




int round_off_image_size(image_header, length, width)
    int    *length, *width;
    struct tiff_header_struct *image_header;
{
   *length = (ROWS-10 + image_header->image_length)/ROWS;
   *width  = (COLS-10 + image_header->image_width)/COLS;
   return(1);
} /* ends round_off_image_size */



int print_bmp_file_header(struct bmpfileheader *file_header)
{
 printf("\nfile type %x", file_header->filetype);
 printf("\nfile size %lu", file_header->filesize);
 printf("\nbit map offset %lu", file_header->bitmapoffset);
 return(1);
}



int read_bm_header(file_name,
               bmheader)
   char *file_name;
   struct bitmapheader *bmheader;
{
   char  buffer[10];
   long  ll;
   short ss;
   unsigned long  ull;
   unsigned short uss;
   FILE *fp;

   fp = fopen(file_name, "rb");


   fseek(fp, 14, SEEK_SET);

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   bmheader->size = ull;

   fread(buffer, 1, 4, fp);
   extract_long_from_buffer(buffer, 1, 0, &ll);
   bmheader->width = ll;

   fread(buffer, 1, 4, fp);
   extract_long_from_buffer(buffer, 1, 0, &ll);
   bmheader->height = ll;

   fread(buffer, 1, 2, fp);
   extract_ushort_from_buffer(buffer, 1, 0, &uss);
   bmheader->planes = uss;

   fread(buffer, 1, 2, fp);
   extract_ushort_from_buffer(buffer, 1, 0, &uss);
   bmheader->bitsperpixel = uss;

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   bmheader->compression = ull;

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   bmheader->sizeofbitmap = ull;

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   bmheader->horzres = ull;

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   bmheader->vertres = ull;

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   bmheader->colorsused = ull;

   fread(buffer, 1, 4, fp);
   extract_ulong_from_buffer(buffer, 1, 0, &ull);
   bmheader->colorsimp = ull;

   fclose(fp);

 return(1);
}  /* ends read_bm_header */


int print_bm_header(bmheader)
   struct bitmapheader *bmheader;
{
 printf("\nwidth %ld", bmheader->width);
 printf("\nheight %ld", bmheader->height);
 printf("\nplanes %d", bmheader->planes);
 printf("\nbitsperpixel %d", bmheader->bitsperpixel);
 printf("\ncolorsused %lu", bmheader->colorsused);
 printf("\ncolorsimp %lu", bmheader->colorsimp);
 return(1);
}



int read_color_table(file_name, rgb, size)
   char   *file_name;
   struct ctstruct *rgb;
   int    size;
{
   int  i;
   char buffer[10];
   FILE *fp;

   fp = fopen(file_name, "rb");

   fseek(fp, 54, SEEK_SET);

   for(i=0; i<size; i++){
      fread(buffer, 1, 1, fp);
      rgb[i].blue = buffer[0];
      fread(buffer, 1, 1, fp);
      rgb[i].green = buffer[0];
      fread(buffer, 1, 1, fp);
      rgb[i].red = buffer[0];
      fread(buffer, 1, 1, fp);
         /* fourth byte nothing */
   }  /* ends loop over i */

   fclose(fp);

 return(1);
}  /* ends read_color_table */



int print_color_table(struct ctstruct *rgb, int size)
{
   int i;

   for(i=0; i<size; i++){
      printf("\n %d %d %d",
      rgb[i].blue,rgb[i].green,rgb[i].red);
   }  /* ends loop over i */
 return(1);
}  /* ends print_color_table */




int flip_image_array(the_image, rows, cols)
   long   cols, rows;
   short  **the_image;
{
   int  i, j;
   long rd2;
   short **temp;

   temp = allocate_image_array(rows, cols);
   rd2  = rows/2;
   for(i=0; i<rd2; i++){
      for(j=0; j<cols; j++){
         temp[rows-1-i][j] = the_image[i][j];
      }  /* ends loop over j */
   }  /* ends loop over i */

   for(i=rd2; i<rows; i++){
      for(j=0; j<cols; j++){
         temp[rows-1-i][j] = the_image[i][j];
      }  /* ends loop over j */
   }  /* ends loop over i */

   for(i=0; i<rows; i++)
      for(j=0; j<cols; j++)
         the_image[i][j] = temp[i][j];

   free_image_array(temp, rows);
 return(1);
}  /* ends flip_image_array */




int read_bmp_image(file_name, array)
   char  *file_name;
   short **array;
{
   FILE   *fp;
   int    i, j;
   int    negative = 0,
          pad      = 0,
          place    = 0;
   long   colors   = 0,
          height   = 0,
          position = 0,
          width    = 0;
   struct bmpfileheader file_header;
   struct bitmapheader  bmheader;
   struct ctstruct rgb[GRAY_LEVELS+1];
   unsigned char uc;

   read_bmp_file_header(file_name, &file_header);
   read_bm_header(file_name, &bmheader);
   if(bmheader.bitsperpixel != 8){
      printf("\nCannot read image when bits per"
      "pixel is not 8");
      exit(1);
   }

   if(bmheader.colorsused == 0)
      colors = GRAY_LEVELS + 1;
   else
      colors = bmheader.colorsused;
   read_color_table(file_name, &rgb, colors);

   fp = fopen(file_name, "rb");
   fseek(fp, file_header.bitmapoffset, SEEK_SET);

   width = bmheader.width;
   if(bmheader.height < 0){
      height   = bmheader.height * (-1);
      negative = 1;
   }
   else
      height = bmheader.height;

   pad = calculate_pad(width);

   for(i=0; i<height; i++){
      for(j=0; j<width; j++){
         place = fgetc(fp);
         uc = (place & 0xff);
         place = uc;
         array[i][j] = rgb[place].blue;
      }  /* ends loop over j */
      if(pad != 0){
         position = fseek(fp, pad, SEEK_CUR);
      }  /* ends if pad 1= 0 */
   }  /* ends loop over i */

   if(negative == 0)
      flip_image_array(array, height, width);

 return(1);
}  /* ends read_bmp_image */



int create_allocate_bmp_file(file_name,
                         file_header,
                         bmheader)
   char  *file_name;
   struct bmpfileheader *file_header;
   struct bitmapheader  *bmheader;
{
   char buffer[100];
   int  i, pad = 0;
   FILE *fp;

   pad = calculate_pad(bmheader->width);

   bmheader->size         =  40;
   bmheader->planes       =   1;
   bmheader->bitsperpixel =   8;
   bmheader->compression  =   0;
   bmheader->sizeofbitmap = bmheader->height *
                            (bmheader->width + pad);
   bmheader->horzres      = 300;
   bmheader->vertres      = 300;
   bmheader->colorsused   = 256;
   bmheader->colorsimp    = 256;

   file_header->filetype     = 0x4D42;
   file_header->reserved1    =  0;
   file_header->reserved2    =  0;
   file_header->bitmapoffset = 14 +
                               bmheader->size +
                               bmheader->colorsused*4;
   file_header->filesize     = file_header->bitmapoffset +
                               bmheader->sizeofbitmap;

   if((fp = fopen(file_name, "wb")) == NULL){
      printf("\nERROR Could not create file %s",
             file_name);
      exit(2);
   }


   insert_ushort_into_buffer(buffer, 0, file_header->filetype);
   fwrite(buffer, 1, 2, fp);

   insert_ulong_into_buffer(buffer, 0, file_header->filesize);
   fwrite(buffer, 1, 4, fp);

   insert_short_into_buffer(buffer, 0, file_header->reserved1);
   fwrite(buffer, 1, 2, fp);

   insert_short_into_buffer(buffer, 0, file_header->reserved2);
   fwrite(buffer, 1, 2, fp);

   insert_ulong_into_buffer(buffer, 0, file_header->bitmapoffset);
   fwrite(buffer, 1, 4, fp);



   insert_ulong_into_buffer(buffer, 0, bmheader->size);
   fwrite(buffer, 1, 4, fp);

   insert_long_into_buffer(buffer, 0, bmheader->width);
   fwrite(buffer, 1, 4, fp);

   insert_long_into_buffer(buffer, 0, bmheader->height);
   fwrite(buffer, 1, 4, fp);

   insert_ushort_into_buffer(buffer, 0, bmheader->planes);
   fwrite(buffer, 1, 2, fp);

   insert_ushort_into_buffer(buffer, 0, bmheader->bitsperpixel);
   fwrite(buffer, 1, 2, fp);

   insert_ulong_into_buffer(buffer, 0, bmheader->compression);
   fwrite(buffer, 1, 4, fp);

   insert_ulong_into_buffer(buffer, 0, bmheader->sizeofbitmap);
   fwrite(buffer, 1, 4, fp);

   insert_ulong_into_buffer(buffer, 0, bmheader->horzres);
   fwrite(buffer, 1, 4, fp);

   insert_ulong_into_buffer(buffer, 0, bmheader->vertres);
   fwrite(buffer, 1, 4, fp);

   insert_ulong_into_buffer(buffer, 0, bmheader->colorsused);
   fwrite(buffer, 1, 4, fp);

   insert_ulong_into_buffer(buffer, 0, bmheader->colorsimp);
   fwrite(buffer, 1, 4, fp);


   buffer[0] = 0x00;

   for(i=0; i<(256*4); i++)
      fwrite(buffer, 1, 1, fp);

   buffer[0] = 0x00;

   for(i=0; i<bmheader->sizeofbitmap; i++)
      fwrite(buffer, 1, 1, fp);

   fclose(fp);

 return(1);
}  /* ends create_allocate_bmp_file */




int create_bmp_file_if_needed(in_name, out_name, out_image)
   char in_name[], out_name[];
   short **out_image;
{
   int    length, width;
   struct bmpfileheader file_header;
   struct bitmapheader  bmheader;

   if(does_not_exist(out_name)){
      printf("\n\n output file does not exist %s",
               out_name);
      read_bm_header(in_name, &bmheader);
      create_allocate_bmp_file(out_name, &file_header, &bmheader);
      printf("\nBFIN> Created %s", out_name);
   }  /* ends if does_not_exist */
 return(1);
}  /* ends bmp_file_if_needed */



int write_bmp_image(file_name, array)
   char   *file_name;
   short  **array;
{
   char   *buffer, c;
   FILE   *image_file;
   int    pad = 0,
          position;
   int    bytes, i, j;
   long   height = 0, width = 0;
   struct bitmapheader  bmheader;
   struct bmpfileheader file_header;
   struct ctstruct rgb[GRAY_LEVELS+1];
   union  short_char_union scu;

   read_bmp_file_header(file_name, &file_header);
   read_bm_header(file_name, &bmheader);

   height = bmheader.height;
   width  = bmheader.width;
   if(height < 0) height = height*(-1);

   buffer = (char  *) malloc(width * sizeof(char ));
   for(i=0; i<width; i++)
      buffer[i] = '\0';

   image_file = fopen(file_name, "rb+");


   position   = fseek(image_file, 54, SEEK_SET);
   for(i=0; i<GRAY_LEVELS+1; i++){
      rgb[i].blue  = i;
      rgb[i].green = i;
      rgb[i].red   = i;
   }  /* ends loop over i */

   for(i=0; i<bmheader.colorsused; i++){
      buffer[0] = rgb[i].blue;
      fwrite(buffer , 1, 1, image_file);
      buffer[0] = rgb[i].green;
      fwrite(buffer , 1, 1, image_file);
      buffer[0] = rgb[i].red;
      fwrite(buffer , 1, 1, image_file);
      buffer[0] = 0x00;
      fwrite(buffer , 1, 1, image_file);
   }  /* ends loop over i */

   position   = fseek(image_file,
                      file_header.bitmapoffset,
                      SEEK_SET);

   pad = calculate_pad(width);

   for(i=0; i<height; i++){
      for(j=0; j<width; j++){

         if(bmheader.bitsperpixel == 8){
            scu.s_num = 0;
            if(bmheader.height > 0)
               scu.s_num = array[height-1-i][j];
            else
               scu.s_num = array[i][j];
            buffer[j] = scu.s_alpha[0];
         }  /* ends if bits_per_pixel == 8 */
         else{
            printf("\nERROR bitsperpixel is not 8");
            exit(1);
         }
      }  /* ends loop over j */

      bytes = fwrite(buffer, 1, width, image_file);

      if(pad != 0){
         for(j=0; j<pad; j++)
            buffer[j] = 0x00;
         fwrite(buffer, 1, pad, image_file);
      }  /* ends if pad != 0 */

   }  /* ends loop over i */

   fclose(image_file);
   free(buffer);
 return(1);
}  /* ends write_bmp_image */



int get_image_size(file_name, rows, cols)
   char *file_name;
   long *cols, *rows;
{
   int is_bmp  = 0,
       is_tiff = 0,
       result  = 0;
   struct bitmapheader bmph;
   struct tiff_header_struct tiffh;

   if(is_a_bmp(file_name)){
      is_bmp = 1;
      read_bm_header(file_name, &bmph);
      *rows = bmph.height;
      *cols = bmph.width;
   }  /* ends if is_a_bmp */

   if(is_a_tiff(file_name)){
      is_tiff = 1;
      read_tiff_header(file_name, &tiffh);
      *rows = tiffh.image_length;
      *cols = tiffh.image_width;
   }  /* ends if is_a_bmp */

   if(is_bmp == 1  ||  is_tiff == 1)
      result = 1;

   return(result);
}  /* ends get_image_size */




int get_bitsperpixel(file_name, bitsperpixel)
   char *file_name;
   long *bitsperpixel;
{
   int    is_bmp  = 0,
          is_tiff = 0,
          result  = 0;
   long   temp;
   struct bitmapheader bmph;
   struct tiff_header_struct tiffh;

   if(is_a_bmp(file_name)){
      is_bmp = 1;
      read_bm_header(file_name, &bmph);
      temp = (long)bmph.bitsperpixel;
      *bitsperpixel = temp;
   }  /* ends if is_a_bmp */

   if(is_a_tiff(file_name)){
      is_tiff = 1;
      read_tiff_header(file_name, &tiffh);
      *bitsperpixel = tiffh.bits_per_pixel;
   }  /* ends if is_a_bmp */

   if(is_bmp == 1  ||  is_tiff == 1)
      result = 1;

   return(result);
}  /* ends get_image_size */




int get_lsb(name)
   char *name;
{
   int   result = 0;
   struct tiff_header_struct tiff_header;

   if(is_a_bmp(name))
      result = 1;

   if(is_a_tiff(name)){
      read_tiff_header(name, &tiff_header);
      if(tiff_header.lsb == 1)
         result = 1;
   }  /* ends if is a tiff */

   return(result);

}  /*  ends get_lsb */



int read_image_array(file_name, array)
   char  *file_name;
   short **array;
{
   int ok = 0;

   if(is_a_tiff(file_name)){
      read_tiff_image(file_name, array);
      ok = 1;
   }

   if(is_a_bmp(file_name)){
      read_bmp_image(file_name, array);
      ok = 1;
   }

   if(ok == 0){
      printf("\nERROR could not read file %s",
             file_name);
      exit(1);
   }

 return(1);
}  /* ends read_image_array */




int write_image_array(file_name, array)
   char  *file_name;
   short **array;
{
   int ok = 0;

   if(is_a_tiff(file_name)){
      write_tiff_image(file_name, array);
      ok = 1;
   }

   if(is_a_bmp(file_name)){
      write_bmp_image(file_name, array);
      ok = 1;
   }

   if(ok == 0){
      printf("\nERROR could not write file %s",
             file_name);
      exit(1);
   }

 return(1);
}  /* ends write_image_array */



int equate_tiff_headers(src, dest)
   struct tiff_header_struct *src, *dest;
{
   dest->lsb            = src->lsb;
   dest->bits_per_pixel = src->bits_per_pixel;
   dest->image_length   = src->image_length;
   dest->image_width    = src->image_width;
   dest->strip_offset   = src->strip_offset;
 return(1);
}  /* ends equate_tiff_headers */




int equate_bmpfileheaders(src, dest)
   struct bmpfileheader *src, *dest;
{
   dest->filetype     = src->filetype;
   dest->filesize     = src->filesize;
   dest->reserved1    = src->reserved1;
   dest->reserved2    = src->reserved2;
   dest->bitmapoffset = src->bitmapoffset;
 return(1);
}  /* ends equate_bmpfileheaders */



int equate_bitmapheaders(src, dest)
   struct bitmapheader *src, *dest;
{
   dest->size         = src->size;
   dest->width        = src->width;
   dest->height       = src->width;
   dest->planes       = src->planes;
   dest->bitsperpixel = src->bitsperpixel;
   dest->compression  = src->compression;
   dest->sizeofbitmap = src->sizeofbitmap;
   dest->horzres      = src->horzres;
   dest->vertres      = src->vertres;
   dest->colorsused   = src->colorsused;
   dest->colorsimp    = src->colorsimp;
 return(1);
}  /* ends equate_bitmapheader */



int are_not_same_size(file1, file2)
   char *file1, *file2;
{
   int  result = 0;
   long cols1  = 1,
        cols2  = 2,
        rows1  = 3,
        rows2  = 4;

   get_image_size(file1, &rows1, &cols1);
   get_image_size(file2, &rows2, &cols2);

   if(rows1 != rows2  ||  cols1 != cols2)
      result = 1;

   return(result);

}  /* ends are_not_same_size */




int create_file_if_needed(in_name, out_name, array)
   char *in_name, *out_name;
   short **array;
{
   if(is_a_tiff(in_name)){
      create_tiff_file_if_needed(in_name,
                                 out_name,
                                 array);
   }  /* ends if is a tiff */

   if(is_a_bmp(in_name)){
      create_bmp_file_if_needed(in_name,
                                out_name,
                                array);
   }  /* ends if is a tiff */

 return(1);
}  /* ends create_file_if_needed */



int create_image_file(in_name, out_name)
   char *in_name, *out_name;
{
   struct bmpfileheader      bmp_file_header;
   struct bitmapheader       bmheader;
   struct tiff_header_struct tiff_file_header;

   if(is_a_tiff(in_name)){
      read_tiff_header(in_name, &tiff_file_header);
      create_allocate_tiff_file(out_name,
                                &tiff_file_header);
   }

   if(is_a_bmp(in_name)){
      read_bmp_file_header(in_name,
                           &bmp_file_header);
      read_bm_header(in_name, &bmheader);
      create_allocate_bmp_file(out_name,
                               &bmp_file_header,
                               &bmheader);
   }

   return(1);

}  /* ends create_image_file */



int create_resized_image_file(in_name, out_name,
                          length, width)
   char *in_name, *out_name;
   long length, width;
{
   struct bmpfileheader      bmp_file_header;
   struct bitmapheader       bmheader;
   struct tiff_header_struct tiff_file_header;

   if(is_a_tiff(in_name)){
      read_tiff_header(in_name, &tiff_file_header);
      tiff_file_header.image_length = length;
      tiff_file_header.image_width  = width;
      create_allocate_tiff_file(out_name,
                                &tiff_file_header);
   }

   if(is_a_bmp(in_name)){
      read_bmp_file_header(in_name,
                           &bmp_file_header);
      read_bm_header(in_name, &bmheader);
      bmheader.height = length;
      bmheader.width  = width;
      create_allocate_bmp_file(out_name,
                               &bmp_file_header,
                               &bmheader);
   }

 return(1);
}  /* ends create_resided_image_file */



int add_image_array(the_image, out_image, rows, cols, max)
   int    rows, cols;
   short  **the_image,
          **out_image,
          max;
{
   int    i, j;

   for(i=0; i<rows; i++){
      for(j=0; j<cols; j++){
         out_image[i][j] = the_image[i][j] +
                           out_image[i][j];
         if(out_image[i][j] > max)
            out_image[i][j] = max;
      }  /* ends loop over j */
   }  /* ends loop over i */



}  /* ends add_image_array */




int subtract_image_array(the_image, out_image, rows, cols)
   int    rows, cols;
   short  **the_image,
          **out_image;
{
   int    i, j, length, width;

   for(i=0; i<rows; i++){
      for(j=0; j<cols; j++){
         out_image[i][j] = the_image[i][j] -
                           out_image[i][j];
         if(out_image[i][j] < 0)
            out_image[i][j] = 0;
      }  /* ends loop over j */
   }  /* ends loop over i */

}  /* ends subtract_image_array */
