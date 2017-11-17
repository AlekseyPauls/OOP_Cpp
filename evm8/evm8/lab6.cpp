//#include <iostream>
//#include <libusb.h>
//#include <stdio.h>
//using namespace std;
//void printdev(libusb_device *dev);
//void print_serial_number(libusb_device *dev);
//int main() {
//	libusb_device **devs; // ��������� �� ��������� �� ����������,
//						  // ������������ ��� ��������� ������ ���������
//	libusb_context *ctx = NULL; // �������� ������ libusb
//	int r; // ��� ������������ ��������
//	ssize_t cnt; // ����� ��������� USB-���������
//	ssize_t i; // ��������� ���������� ����� �������� ���� ���������
//			   // ���������������� ���������� libusb, ������� ������ ������ � libusb
//	r = libusb_init(&ctx);
//	if (r < 0) {
//		fprintf(stderr,
//			"������: ������������� �� ���������, ���: %d.\n", r);
//		return 1;
//	}
//	// ������ ������� ����������� ���������� ���������
//	libusb_set_debug(ctx, 3);
//	// �������� ������ ���� ��������� USB- ���������
//	cnt = libusb_get_device_list(ctx, &devs);
//	if (cnt < 0) {
//		fprintf(stderr,
//			"������: ������ USB ��������� �� �������.\n", r);
//		return 1;
//	}
//	printf("������� ���������: %d\n", cnt);
//	printf("=============================="
//		"=============================\n");
//	printf("| ����� ����������\n");
//	printf("|  * ������������� �������������\n");
//	printf("|  |    * ������������� ����������\n");
//	printf("+--+----+------\n");
//	for (i = 0; i < cnt; i++) { // ���� �������� ���� ���������
//		printdev(devs[i]); // ������ ���������� ����������
//	}
//	printf("=============================="
//		"=============================\n");
//	// ����� �������� ������� ���������
//	printf("* ������������� ����������\n");
//	printf("     * �������� ����� ����������\n");
//	printf("+----+---------------\n");
//	for (i = 0; i < cnt; i++) { // ���� �������� ���� ���������
//		print_serial_number(devs[i]); // ������ ��������� ������ ����������
//	}
//
//	// ���������� ������, ���������� �������� ��������� ������ ���������
//	libusb_free_device_list(devs, 1);
//	libusb_exit(ctx); // ��������� ������ � ����������� libusb,
//					  // ������� ������ ������ � libusb
//	return 0;
//}
//void printdev(libusb_device *dev) {
//	libusb_device_descriptor desc; // ���������� ����������
//	int r = libusb_get_device_descriptor(dev, &desc);
//	if (r < 0) {
//		fprintf(stderr,
//			"������: ���������� ���������� �� �������, ���: %d.\n", r);
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
//			"������: ���������� ���������� �� �������, ���: %d.\n", r);
//		return;
//	}
//	printf(" %.4d %s\n",
//		desc.idProduct,
//		serial_number);
//	libusb_close(devh);
//}
