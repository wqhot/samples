/**
* @file uart.h
*/

#ifndef UART_ENGINE_H_
#define UART_ENGINE_H_



#define INFO_LOG(fmt, args...) fprintf(stdout, "[INFO]  " fmt "\n", ##args)
#define WARN_LOG(fmt, args...) fprintf(stdout, "[WARN]  " fmt "\n", ##args)
#define ERROR_LOG(fmt, args...) fprintf(stdout, "[ERROR]  " fmt "\n", ##args)
class uart {
public:
    uart(void) ;
    ~uart(void) ;

    int uart_open(void);
    int uart_close(void);
    int uart_send(char *buffer,int size);
    int uart_read(char *buffer,int size);
    int uart_set_option(int nSpeed, int nBits, char nEvent, int nStop);

private:
    int fd;
};

#endif // UART_ENGINE_H_
