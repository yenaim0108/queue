#include <stdio.h>
#include <malloc.h>

#define QUEUE_LENGTH 5           // ť�� ���� ����

struct NODE
{ // ����Ʈ�� ��� ����ü ����
	char data;                   // ���� ����� ��
	struct NODE *nextNodePointer;    // ���� ��� �ּ� ����
};

// �������� ����
struct NODE *headPointer = NULL; // ť�� head ������
struct NODE *tailPointer = NULL; // ť�� tail ������
int headIndex = -1;              // head �����Ͱ� ����Ű�� �ִ� ��尡 �� ��° ������� �����ϴ� ����(0������� ����)
int tailIndex = -1;              // tail �����Ͱ� ����Ű�� �ִ� ��尡 �� ��° ������� �����ϴ� ����(0������� ����)

struct NODE * createQueue()
{ // ť ���� �Լ�
	extern struct NODE *headPointer;
	extern struct NODE *tailPointer;

	// �������� ����
	struct NODE *node = NULL;    // �����Ҵ��� ��带 �����ϴ� ����
	struct NODE *nodeTmp = NULL; // ��ũ�帮��Ʈ�� ����� ���� ���� ����� �ӽ� �������
	struct NODE *first = NULL;   // ť�� �� ���� ��带 ����
	int i;                       // �ݺ����� ������ ���� ����

	i = 0;
	while (i < QUEUE_LENGTH)
	{ // QUEUE_LENGTH�� ���� ��ŭ �ݺ��ؼ� ť�� ��� ����
		node = (struct NODE *)malloc(sizeof(struct NODE)); // node�� �����Ҵ�(= ���� ���)

		if (i == 0)
		{ // ù ��° ����� ���
			first = node;                // ù ��° ��带 header�� ����
			node->nextNodePointer = NULL;    // ù ��° ����̹Ƿ� ���� ��尡 ����.
		}
		else
		{ // �� ��° �̻��� ����� ���
			node->nextNodePointer = first;   // ������ ���(= ���� ���)�� ���� ��带 ù ��° ���� �����ؼ� ȯ��ũ�帮��Ʈ�� ����
			nodeTmp->nextNodePointer = node; // nodeTmp(= ���� ���)�� ���� ��带 ���� ����� �ּҷ� �����ؼ� ��ũ�帮��Ʈ ����
		}

		node->data = '\0';               // ���� �Էµ� ���� �����Ƿ� ������ ������ �ʱ�ȭ
		nodeTmp = node;                  // ���� ��带 nodeTmp�� �ӽ�����(why? ��ũ�帮��Ʈ�� ����� ���ؼ�...)
		i++;
	}

	return first;
}

void queueResultDisplay(struct NODE *resultNodeTmp)
{ // ť �޸� �� head ������ tail ������ ��� �Լ�
	extern int headIndex;
	extern int tailIndex;

	printf("[���]\n");

	// queue ���ȣ ���
	for (int i = 0; i < QUEUE_LENGTH; i++)
	{
		printf("%3d", i + 1);                           // �ڵ������� 0������� ����, �˰���(���)�󿡼��� 1������� ����
	}
	printf("  HEAD  TAIL\n");

	// queue �� ���
	for (int i = 0; i < QUEUE_LENGTH; i++)
	{
		printf("%3c", resultNodeTmp->data);             // ���� ����� ������ ���
		resultNodeTmp = resultNodeTmp->nextNodePointer;     // resultNodeTmp�� ���� ����� �ּҷ� �ٲ�.
	}
	printf("%4d  %4d\n", headIndex + 1, tailIndex + 1); // head, tail ������ �� ��ȣ ���(�˰��� ����)
}

void insertNode(struct NODE *first)
{ // ����Ʈ�� ��� �Է�(= ����) �Լ�
	extern struct NODE *headPointer;
	extern struct NODE *tailPointer;

	//�������� ����
	char data; // ����ڰ� �Է��� ������ ����

	// ����ڰ� ������ �Է�
	printf("\n�Է� : ");
	fflush(stdin);
	scanf("%c", &data);

	// �����÷ο� ó��
	if (((tailIndex - headIndex + 1) >= QUEUE_LENGTH) || ((tailIndex - headIndex + 1) == 0))
	{ /* �������� ������ ť�� ���̺��� ũ�ų� ���� ��� or ����ִ� ������ 0�ΰ�� �����÷ο�
	  (tailCount - headCount + 1)�� �����
	  ����̸� �Էµ� �������� ����, 0�̰ų� �����̸� ����ִ� �������� ���� (tail, head�� �Ѵ� -1�� ���� ����)*/
		printf("�����÷ο��Դϴ�. �����͸� ��� �� �ٽ� �Է����ּ���.\n");
		return;
	}
	else if (tailIndex >= (QUEUE_LENGTH - 1))
	{ // ȯ�� ť ���, �����÷ο찡 �ƴѵ� tailCount�� ť�� (������ ���ȣ - 1)���� ũ�ų� ���� ��� -1(�ʱⰪ)�� �����.
		tailIndex = -1; // ������ �Է��� �� 0�� ��(= first)�� �ֱ� ���ؼ�...

		/* tail�� -1�̶�� �� ť�� �����Ͱ� 0���̰ų�
		ť�� ��밹������ ������ tailCount�� ť�� ���̺��� ũ�ų� ���Ƽ� ���� ���� ���µ� ��������� �ִ� ���
		ex) ť�� ���̰� 5�� ��� : 3, 4, 5�� �濡 �����Ͱ� �ִµ� 1, 2�� ���� ����ִ� ��� */
	}

	// ������ �Է�
	tailIndex += 1;                             // �˰��򿡼��� ������� Ȯ��
	// ���� ���������� ������� Ȯ��
	if ((headIndex == -1) && (tailIndex == 0))
	{ // ť�� ������� �� ó������ �����͸� �Է��ϴ� ���
		tailPointer = first;                    // tail �����Ϳ� ù ��° ����� �ּ� ����    

		headIndex += 1;                         // FIFIO ����, ó�� �Էµ� �����͸� ���� ���� ���
		headPointer = first;                    // FIFIO ����, ó�� �Էµ� �����͸� ���� ���� ���
	}
	else
	{ // ť�� �����Ͱ� 1�� �̻� ���� �� �����͸� �Է��ϴ� ���
		tailPointer = tailPointer->nextNodePointer; // tail �����Ϳ� ���� �Է¹��� �����͸� ������ ����� �ּ� ����

		/* ť�� ���̸� 5��� �� �� 2, 3, 4���濡�� �����Ͱ� ������
		0, 1�� �濡�� �����Ͱ� ���°��(tailCount : 4, headCount : 2) �����÷ο찡 �ƴϱ� ������
		ȯ�� ť ������� ó���ؼ� ������ �ԷµǴ� �����ʹ� 0����(= first)�� ����ǰ� �Ѵ�.
		�̶�, ť�� ȯ��ũ�帮��Ʈ�̹Ƿ� tail �������� next �����ʹ� first(= tailCount : 0)�� �ȴ�.
		�׷��� if���� ������ ((headCount != -1) && tailCount == 0)�� �Ἥ
		ȯ��ť ������� 0�� ��(= first)�� �Է��ϴ� ��츦 ���� ���� ó���� �� �ʿ䰡 ���
		if���� ������ ((headCount == -1) && (tailCount == 0))�� �Ἥ
		ť�� ������� �� ó������ �����͸� �Է��ϴ� ��츸 ���� ó���ߴ�. */
	}
	tailPointer->data = data;                   // tail �����Ͱ� ����Ű�� �ִ� ��忡 ������ ����

	// ť�� ���� ���� ���
	queueResultDisplay(first);
}

void deleteNode(struct NODE *first)
{ // ����Ʈ�� ��� ���(= ����) �Լ�
	extern struct NODE *headPointer;
	extern struct NODE *tailPointer;

	// ����÷ο� ó��
	if (headIndex <= -1)
	{ // head�� -1���� �۰ų� ���� ù ��° ��忡 �����Ͱ� ���� ��� ����÷ο�
		printf("����÷ο��Դϴ�. �����͸� �Է� �� �ٽ� ����ϼ���.\n");
		return;
	}

	// ������ ���
	headPointer->data = '\0';

	// ������ ����� ����Ѱ�� -1(�ʱⰪ)���� �����
	if ((headIndex == (QUEUE_LENGTH - 1)) && (tailIndex != (QUEUE_LENGTH - 1)))
	{
		headIndex = -1;
	}

	// ������ ��� �� head���ٰ� �������� ���� ��� �켱������ ������ �ִ� ��� ����
	headIndex += 1;                         // �˰��򿡼��� ���
	headPointer = headPointer->nextNodePointer; // ���� ���������� ���

	// �����͸� ��� ����ؼ� ť�� ����ִ°�� head�� tail�� -1(�ʱⰪ)���� �����
	if ((headIndex - tailIndex) == 1)
	{
		headIndex = -1;
		tailIndex = -1;
	}

	// ť�� ���� ���� ���
	queueResultDisplay(first);
}