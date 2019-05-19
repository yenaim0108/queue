#include <stdio.h>
#include "CircularQueue.h"

#define TRUE  1
#define FALSE 0

void main()
{
	// �������� ����
	int option = 0;                   // �Է�, ���, ���� �߿��� ����ڰ� ������ �ɼ� ����
	int no_match = FALSE;             // �ش��ϴ� �ɼ��� ������ �ٽ� �Է¹ޱ�.
	int exit = FALSE;                 // ���α׷� ���� ���� Ȯ��
	struct NODE *first;               // ť�� �� ���� ��带 ����

	printf("\nť : ȯ��ť(Circular Queue)���\n");

	first = createQueue();            // ť ����

	while (1)
	{
		printf("\n   <��ȣ�� �����ϼ���.>\n1. �Է�  2. ���  3. ����\n���� : ");
		scanf("%d", &option);         // ����ڰ� �ɼ� ����

		// ����ڰ� ������ �ɼ�
		switch (option)
		{
		case 1:
			insertNode(first); break;  // ����� ������ ����
		case 2:
			deleteNode(first); break; // ����� ������ ����	
		case 3:
			printf("���α׷��� �����մϴ�.\n");
			exit = TRUE;
			break;
		default:
			printf("�ش��ϴ� �ɼ��� �����ϴ�.\n");
			no_match = TRUE;
		}

		if (no_match)
		{
			no_match = FALSE;
			continue;                 // �ش��ϴ� �ɼ��� ������ �ٽ� �Է¹ޱ�
		}

		if (exit)
		{
			break;                    // ����ڰ� ���Ḧ ���ϸ� ���α׷� ����
		}
	}
}