//#include <iostream>
//#include <libusb.h>
//#include <stdio.h>
//using namespace std;
//void printdev(libusb_device *dev);
//void print_serial_number(libusb_device *dev);
//int main() {
//	libusb_device **devs; // указатель на указатель на устройство,
//						  // используется для получения списка устройств
//	libusb_context *ctx = NULL; // контекст сессии libusb
//	int r; // для возвращаемых значений
//	ssize_t cnt; // число найденных USB-устройств
//	ssize_t i; // индексная переменная цикла перебора всех устройств
//			   // инициализировать библиотеку libusb, открыть сессию работы с libusb
//	r = libusb_init(&ctx);
//	if (r < 0) {
//		fprintf(stderr,
//			"Ошибка: инициализация не выполнена, код: %d.\n", r);
//		return 1;
//	}
//	// задать уровень подробности отладочных сообщений
//	libusb_set_debug(ctx, 3);
//	// получить список всех найденных USB- устройств
//	cnt = libusb_get_device_list(ctx, &devs);
//	if (cnt < 0) {
//		fprintf(stderr,
//			"Ошибка: список USB устройств не получен.\n", r);
//		return 1;
//	}
//	printf("найдено устройств: %d\n", cnt);
//	printf("=============================="
//		"=============================\n");
//	printf("| класс устройства\n");
//	printf("|  * идентификатор производителя\n");
//	printf("|  |    * идентификатор устройства\n");
//	printf("+--+----+------\n");
//	for (i = 0; i < cnt; i++) { // цикл перебора всех устройств
//		printdev(devs[i]); // печать параметров устройства
//	}
//	printf("=============================="
//		"=============================\n");
//	// Вывод серийных номеров устройств
//	printf("* идентификатор устройства\n");
//	printf("     * серийный номер устройства\n");
//	printf("+----+---------------\n");
//	for (i = 0; i < cnt; i++) { // цикл перебора всех устройств
//		print_serial_number(devs[i]); // печать серийного номера устройства
//	}
//
//	// освободить память, выделенную функцией получения списка устройств
//	libusb_free_device_list(devs, 1);
//	libusb_exit(ctx); // завершить работу с библиотекой libusb,
//					  // закрыть сессию работы с libusb
//	return 0;
//}
//void printdev(libusb_device *dev) {
//	libusb_device_descriptor desc; // дескриптор устройства
//	int r = libusb_get_device_descriptor(dev, &desc);
//	if (r < 0) {
//		fprintf(stderr,
//			"Ошибка: дескриптор устройства не получен, код: %d.\n", r);
//		return;
//	}
//	printf(" %.2d %.4d %.4d\n",
//		(int)desc.bDeviceClass,
//		desc.idVendor,
//		desc.idProduct
//	);
//}
//
//void print_serial_number(libusb_device *dev) {
//	unsigned char serial_number[50];
//	libusb_device_handle *devh = NULL;
//	libusb_device_descriptor desc;
//	int r = libusb_get_device_descriptor(dev, &desc);
//	if (r < 0) {
//		fprintf(stderr,
//			"Ошибка: дескриптор устройства не получен, код: %d.\n", r);
//		return;
//	}
//	printf(" %.4d %s\n",
//		desc.idProduct,
//		serial_number);
//	libusb_close(devh);
//}
