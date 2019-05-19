struct NODE * createQueue();                         // 큐를 QUEUE_LENGTH만큼 생성
void queueResultDisplay(struct NODE *resultNodeTmp); // 큐 메모리 및 head 포인터 tail 포인터 출력 함수
void insertNode(struct NODE *first);                 // 리스트의 노드 입력(= 삽입) 함수
void deleteNode(struct NODE *first);                 // 리스트의 노드 출력(= 삭제) 함수