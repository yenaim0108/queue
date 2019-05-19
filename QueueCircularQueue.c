#include <stdio.h>
#include <malloc.h>

#define QUEUE_LENGTH 5           // 큐의 길이 지정

struct NODE
{ // 리스트의 노드 구조체 정의
	char data;                   // 현재 노드의 값
	struct NODE *nextNodePointer;    // 다음 노드 주소 저장
};

// 전역변수 선언
struct NODE *headPointer = NULL; // 큐의 head 포인터
struct NODE *tailPointer = NULL; // 큐의 tail 포인터
int headIndex = -1;              // head 포인터가 가리키고 있는 노드가 몇 번째 노드인지 저장하는 변수(0번방부터 시작)
int tailIndex = -1;              // tail 포인터가 가리키고 있는 노드가 몇 번째 노드인지 저장하는 변수(0번방부터 시작)

struct NODE * createQueue()
{ // 큐 생성 함수
	extern struct NODE *headPointer;
	extern struct NODE *tailPointer;

	// 지역변수 선언
	struct NODE *node = NULL;    // 동적할당한 노드를 저장하는 변수
	struct NODE *nodeTmp = NULL; // 링크드리스트를 만들기 위한 현재 노드의 임시 저장공간
	struct NODE *first = NULL;   // 큐의 맨 앞의 노드를 저장
	int i;                       // 반복문을 돌리기 위한 변수

	i = 0;
	while (i < QUEUE_LENGTH)
	{ // QUEUE_LENGTH의 길이 만큼 반복해서 큐의 노드 생성
		node = (struct NODE *)malloc(sizeof(struct NODE)); // node에 동적할당(= 현재 노드)

		if (i == 0)
		{ // 첫 번째 노드일 경우
			first = node;                // 첫 번째 노드를 header에 저장
			node->nextNodePointer = NULL;    // 첫 번째 노드이므로 다음 노드가 없다.
		}
		else
		{ // 두 번째 이상의 노드일 경우
			node->nextNodePointer = first;   // 마지막 노드(= 현재 노드)의 다음 노드를 첫 번째 노드로 저장해서 환상링크드리스트로 생성
			nodeTmp->nextNodePointer = node; // nodeTmp(= 이전 노드)의 다음 노드를 현재 노드의 주소로 저장해서 링크드리스트 생성
		}

		node->data = '\0';               // 아직 입력된 값이 없으므로 스택의 데이터 초기화
		nodeTmp = node;                  // 현재 노드를 nodeTmp에 임시저장(why? 링크드리스트를 만들기 위해서...)
		i++;
	}

	return first;
}

void queueResultDisplay(struct NODE *resultNodeTmp)
{ // 큐 메모리 및 head 포인터 tail 포인터 출력 함수
	extern int headIndex;
	extern int tailIndex;

	printf("[결과]\n");

	// queue 방번호 출력
	for (int i = 0; i < QUEUE_LENGTH; i++)
	{
		printf("%3d", i + 1);                           // 코딩에서는 0번방부터 시작, 알고리즘(출력)상에서는 1번방부터 시작
	}
	printf("  HEAD  TAIL\n");

	// queue 값 출력
	for (int i = 0; i < QUEUE_LENGTH; i++)
	{
		printf("%3c", resultNodeTmp->data);             // 현재 노드의 데이터 출력
		resultNodeTmp = resultNodeTmp->nextNodePointer;     // resultNodeTmp를 다음 노드의 주소로 바꿈.
	}
	printf("%4d  %4d\n", headIndex + 1, tailIndex + 1); // head, tail 포인터 방 번호 출력(알고리즘 기준)
}

void insertNode(struct NODE *first)
{ // 리스트의 노드 입력(= 삽입) 함수
	extern struct NODE *headPointer;
	extern struct NODE *tailPointer;

	//지역변수 선언
	char data; // 사용자가 입력한 데이터 저장

	// 사용자가 데이터 입력
	printf("\n입력 : ");
	fflush(stdin);
	scanf("%c", &data);

	// 오버플로우 처리
	if (((tailIndex - headIndex + 1) >= QUEUE_LENGTH) || ((tailIndex - headIndex + 1) == 0))
	{ /* 데이터의 갯수가 큐의 길이보다 크거나 같은 경우 or 비어있는 갯수가 0인경우 오버플로우
	  (tailCount - headCount + 1)의 결과가
	  양수이면 입력된 데이터의 갯수, 0이거나 음수이면 비어있는 데이터의 갯수 (tail, head가 둘다 -1인 경우는 예외)*/
		printf("오버플로우입니다. 데이터를 출력 후 다시 입력해주세요.\n");
		return;
	}
	else if (tailIndex >= (QUEUE_LENGTH - 1))
	{ // 환상 큐 방식, 오버플로우가 아닌데 tailCount가 큐의 (마지막 방번호 - 1)보다 크거나 같은 경우 -1(초기값)로 만든다.
		tailIndex = -1; // 다음에 입력할 때 0번 방(= first)에 넣기 위해서...

		/* tail이 -1이라는 건 큐의 데이터가 0개이거나
		큐의 허용갯수보다 작은데 tailCount가 큐의 길이보다 크거나 같아서 넣을 수가 없는데 가용공간이 있는 경우
		ex) 큐의 길이가 5일 경우 : 3, 4, 5번 방에 데이터가 있는데 1, 2번 방은 비어있는 경우 */
	}

	// 데이터 입력
	tailIndex += 1;                             // 알고리즘에서의 저장공간 확보
	// 실제 구현에서의 저장공간 확보
	if ((headIndex == -1) && (tailIndex == 0))
	{ // 큐가 비어있을 때 처음으로 데이터를 입력하는 경우
		tailPointer = first;                    // tail 포인터에 첫 번째 노드의 주소 저장    

		headIndex += 1;                         // FIFIO 구조, 처음 입력된 데이터를 가장 먼저 출력
		headPointer = first;                    // FIFIO 구조, 처음 입력된 데이터를 가장 먼저 출력
	}
	else
	{ // 큐의 데이터가 1개 이상 있을 때 데이터를 입력하는 경우
		tailPointer = tailPointer->nextNodePointer; // tail 포인터에 현재 입력받은 데이터를 삽입할 노드의 주소 저장

		/* 큐의 길이를 5라고 할 때 2, 3, 4번방에는 데이터가 있지만
		0, 1번 방에는 데이터가 없는경우(tailCount : 4, headCount : 2) 오버플로우가 아니기 때문에
		환상 큐 방식으로 처리해서 다음에 입력되는 데이터는 0번방(= first)에 저장되게 한다.
		이때, 큐는 환상링크드리스트이므로 tail 포인터의 next 포인터는 first(= tailCount : 0)가 된다.
		그래서 if문의 조건을 ((headCount != -1) && tailCount == 0)로 써서
		환상큐 방식으로 0번 방(= first)에 입력하는 경우를 따로 빼서 처리해 줄 필요가 없어서
		if문의 조건을 ((headCount == -1) && (tailCount == 0))로 써서
		큐가 비어있을 때 처음으로 데이터를 입력하는 경우만 따로 처리했다. */
	}
	tailPointer->data = data;                   // tail 포인터가 가리키고 있는 노드에 데이터 삽입

	// 큐의 현재 상태 출력
	queueResultDisplay(first);
}

void deleteNode(struct NODE *first)
{ // 리스트의 노드 출력(= 삭제) 함수
	extern struct NODE *headPointer;
	extern struct NODE *tailPointer;

	// 언더플로우 처리
	if (headIndex <= -1)
	{ // head가 -1보다 작거나 같고 첫 번째 노드에 데이터가 없는 경우 언더플로우
		printf("언더플로우입니다. 데이터를 입력 후 다시 출력하세요.\n");
		return;
	}

	// 데이터 출력
	headPointer->data = '\0';

	// 마지막 방까지 출력한경우 -1(초기값)으로 만들기
	if ((headIndex == (QUEUE_LENGTH - 1)) && (tailIndex != (QUEUE_LENGTH - 1)))
	{
		headIndex = -1;
	}

	// 데이터 출력 후 head에다가 다음으로 높은 출력 우선순위를 가지고 있는 노드 저장
	headIndex += 1;                         // 알고리즘에서의 방식
	headPointer = headPointer->nextNodePointer; // 실제 구현에서의 방식

	// 데이터를 모두 출력해서 큐가 비어있는경우 head와 tail을 -1(초기값)으로 만들기
	if ((headIndex - tailIndex) == 1)
	{
		headIndex = -1;
		tailIndex = -1;
	}

	// 큐의 현재 상태 출력
	queueResultDisplay(first);
}