#ifndef _MO_MANDELBROT_H
#define _MO_MANDELBROT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <mpi.h>

#define MO_N 2                    
#define MO_THRESHOLD 4                    
#define MO_SIZE 1024                 
#define MO_FILENAME "./mandelbrot.bmp"  
#define MO_MAXITER 2000                 
#define MO_BLOCKSIZE 1                   
                                              
#define MO_COLORMIN 0x000000             
#define MO_COLORMAX 0xffffff            
#define MO_COLORMASK 0xffffff             
#define MO_PROGRESS 0                    
#define MO_PWIDTH 50                   
#define MO_PUPDATE 20                   

#define MO_CALC 1                    
#define MO_DATA 2                   
#define MO_STOP 3                    

#define eprintf(...) { \
    fprintf(stderr, "Error: "); \
    fprintf(stderr, __VA_ARGS__); \
}

#define finalize_exit(error_code) { \
    MPI_Finalize(); \
    exit((error_code)); \
}

typedef struct _mo_complex {
    double re;                
    double im;                 
} mo_complex_t;

typedef struct _mo_opts {
    int width, height;         
    char *filename;             
    double max_re, min_re;      
    double max_im, min_im;      
    int max_iterations;        
    int blocksize;              
    long min_color, max_color;  
    long color_mask;            
    int show_progress;          
} mo_opts_t;

typedef struct _mo_scale {
    double color, im, re;                                
} mo_scale_t;

typedef struct _mo_bmp_header {
    char type[2];            
    int fsize;                 
    int reserved;              
    int offbits;              
    int hsize;             
    int width;                 
    int height;              
    short planes;             
    short bit_count;           
    int compression;            
    int size_image;             
    int x_pels_per_meter;     
    int y_pels_per_meter;      
    int clr_used;                                       
    int clr_important;               
} mo_bmp_header_t;

static int parse_args(int, char **, mo_opts_t *, int, int);
static void print_params(mo_opts_t *, double, double, double);
static void print_usage(char **);
static int master_proc(int, mo_opts_t *);
static int slave_proc(int, mo_opts_t *);
static long mandelbrot(int, int, mo_scale_t *, mo_opts_t *);
static inline void print_progress(int, int);
static int write_bitmap(const char *, int, int, char *);

#endif