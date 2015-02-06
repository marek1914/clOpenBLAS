#define ALLOC_SIZE (4096*4096*4)

#define SGEMM_M_MAX (1024*4)
#define SGEMM_N_MAX (1024*4)
#define SGEMM_K_MAX (1024*4)

#define DGEMM_M_MAX (1024*2)
#define DGEMM_N_MAX (1024*2)
#define DGEMM_K_MAX (1024*4)

#define SGEMM_N_BUFFERS 16
#define DGEMM_N_BUFFERS 16

#define GALLOC_SIZE_A ( SGEMM_M_MAX * SGEMM_K_MAX * sizeof(float) )
#define GALLOC_SIZE_B ( SGEMM_N_MAX * SGEMM_K_MAX * sizeof(float) )
#define GALLOC_SIZE_C ( SGEMM_M_MAX * SGEMM_N_MAX * sizeof(float) )

#define MALLOC_SIZE_A GALLOC_SIZE_A
#define MALLOC_SIZE_B ( GALLOC_SIZE_B * ( SGEMM_N_BUFFERS + 1 ) )
#define MALLOC_SIZE_C GALLOC_SIZE_C

#define SGEMM_GLOBAL0_DIV 8
#define SGEMM_GLOBAL1_DIV 4

#define SGEMM_LOCAL0 16
#define SGEMM_LOCAL1 16

#define SGEMM_PAD_M 128
#define SGEMM_PAD_N 64
#define SGEMM_PAD_K 16

#define DGEMM_GLOBAL0_DIV 8
#define DGEMM_GLOBAL1_DIV 4

#define DGEMM_LOCAL0 16
#define DGEMM_LOCAL1 16

#define DGEMM_PAD_M 128
#define DGEMM_PAD_N 64
#define DGEMM_PAD_K 16


static char  *DEFAULT_KERNEL = "geforce_7xx";

static char  *DEFAULT_DEVICE = "geforce_gtx_7";



struct gpu_context
{
        int                     platform;
        int                     device;
        int                     unified_mem;
        cl_platform_id          platform_id;
        cl_device_id            device_id;
        cl_context              context;
        cl_program              program;
        cl_kernel               kernel;
        cl_command_queue        command_queue;
        cl_mem                  A;
        cl_mem                  B;
        cl_mem                  C;
        void*                   hA;
        void*                   hB;
        void*                   hC;
        char                    device_name[64];
};

static int  create_gpu_context(struct gpu_context *gpu);
static int  create_gpu_program_nonunified(struct gpu_context *gpu, char *func ,size_t bufsize);
static void destroy_gpu_context(struct gpu_context *gpu);
static void release_gpu_program(struct gpu_context *gpu);

static void open_gpu()  __attribute__((constructor));
static void close_gpu() __attribute__((destructor));

static void sgemm_gpu_ccopy(int M, int N, float *A, int LDA, float *B, blasint LDB, float beta) __attribute__ ((noinline));
static void sgemm_gpu_acopy(int M, int N, float *A , blasint LDA, float *B, int PAD_M, int PAD_N) __attribute__ ((noinline));
static void sgemm_gpu_btcopy(int M, int N, float *A , blasint LDA, float *B, int PAD_M, int PAD_N) __attribute__ ((noinline));
static void sgemm_gpu_bcopy(int M, int N, float *A , blasint LDA, float *B, int PAD_M, int PAD_N) __attribute__ ((noinline));
static int  sgemm_gpu_kernel(struct gpu_context *gpu_ptr, int M, int N, int K, float ALPHA, int acopy, int bcopy, double *ktime) __attribute__ ((noinline));


static void dgemm_gpu_ccopy(int M, int N, double *A, int LDA, double *B, blasint LDB, double beta) __attribute__ ((noinline));
static void dgemm_gpu_acopy(int M, int N, double *A , blasint LDA, double *B, int PAD_M, int PAD_N) __attribute__ ((noinline));
static void dgemm_gpu_btcopy(int M, int N, double *A , blasint LDA, double *B, int PAD_M, int PAD_N) __attribute__ ((noinline));
static void dgemm_gpu_bcopy(int M, int N, double *A , blasint LDA, double *B, int PAD_M, int PAD_N) __attribute__ ((noinline));
static int  dgemm_gpu_kernel(struct gpu_context *gpu_ptr, int M, int N, int K, double ALPHA, int acopy, int bcopy, double *ktime) __attribute__ ((noinline));




