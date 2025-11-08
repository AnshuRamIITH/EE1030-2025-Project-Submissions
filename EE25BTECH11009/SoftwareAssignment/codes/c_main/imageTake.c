#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include "imageTake.h"
#include <string.h>
#include <ctype.h>  

matrix *read_image(const char *file ){
    int width , height , color_bw;//color_bw = no of color channels , 
    unsigned char *data =stbi_load(file ,&width,&height,&color_bw,1);//here 1 forces image to be loaded on greyscale
    //stbi_load :fnc defined on stb_image library 
    if(!data){
        fprintf( stderr," failed to load image %s\n",file);
        exit(1); //closes the program imdiately 
    }
    matrix *img =make_matrix(height,width);
    for(int i=0; i<height;i++){
        for(int j=0;j<width;j++){
            img->data[i][j]=(double)data[i*width +j];
        }
    }
    stbi_image_free(data);
        printf("Image loaded : %s(%dx %d)",file,height,width);
    return img;
    
}

void write_image(const char* file , matrix*img){
    const char* ext =strrchr (file,'.');//strrchr searches the last occurance of '.' 
    //so that we could know which extention is used 
    if (!ext) ext = ".jpg"; // default we are taking in jpg

    int width= img-> cols;
    int height = img ->rows;
    unsigned char* data = malloc (width * height);
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            double val=img->data[i][j];//reading pxiel value
            if(val<0)val=0;
            if(val>255)val=255;//adding limitations ;
            data[i*width +j]=(unsigned char)val;//imgage lib want in this type so typecast 
    
        }
    }
    //used llm to understand working of stb_image
    //and little syntax used 
    int success = 0;//for checking that it works 
    if (strcasecmp(ext, ".pgm") == 0) { //strcasecmp compares case insensitive 
        FILE* fp = fopen( file, "wb"); //wb - write binary 
        fprintf (fp, "P5\n%d %d\n255\n" , width, height) ;//basic format of image in pgm 
        fwrite (data, 1, width * height, fp) ;
        fclose (fp);
        success = 1;
    } else if (strcasecmp (ext,".jpg") == 0 ||strcasecmp (ext, ".jpeg") == 0) {
        success = stbi_write_jpg (file, width, height, 1, data, 90); // 90 is the qaulity written in jpg format while using std_image 
    }else if ( strcasecmp(ext,  ".png" )== 0) {                      //90 he isiliye liye kyuki ye pixel rounding errors ko negligible kr deta hai
        success = stbi_write_png (file, width, height, 1, data, width);
    } else {
        success = stbi_write_jpg(file , width, height, 1, data, 90) ; // Default to jpg
    }

    if (!(success) ) fprintf( stderr, " Failed to write %s\n", file);
    else printf(" Image written to %s\n", file);

    free(data);

}


