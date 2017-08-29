/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include <Json.h>
#include <Tos_Mema.h>
#include <text.h>

JSON_Node *Json_New_Node()
{
	JSON_Node *Node;
	Node=Mema_Malloc(sizeof(JSON_Node));
	BufferFill(Node,0x00,sizeof(JSON_Node));
	return Node;
}
void Json_Del_Node(JSON_Node *JNCur)
{
	Mema_Free(JNCur);
}
void Json_Add_Next(JSON_Node *JNCur,JSON_Node *JNNext)
{
	JNCur->Next=JNNext;
}
void Json_Del_Next(JSON_Node *JNCur)
{
	JNCur->Next=Null;
}
void Json_Add_Son(JSON_Node *JNCur,JSON_Node *JNSon)
{
	JNCur->Son=JNSon;
}
void Json_Del_Son(JSON_Node *JNCur,JSON_Node *JNSon)
{
	JNCur->Son=Null;
}
void Json_SetString(JSON_Node *JNCur,uint8 *Option,void *Value)
{
	JNCur->Option=Option;
	JNCur->Value=Value;
	JNCur->Type=JOT_String;
}
void Json_SetNode(JSON_Node *JNCur,uint8 *Option,void *Value)
{
	JNCur->Option=Option;
	JNCur->Value=Value;
	JNCur->Type=JOT_Node;
}
void Json_SetInt(JSON_Node *JNCur,uint8 *Option,void *Value)
{
	JNCur->Option=Option;
	JNCur->Value=Value;
	JNCur->Type=JOT_Int;
}
void Json_SetFloat(JSON_Node *JNCur,uint8 *Option,void *Value)
{
	JNCur->Option=Option;
	JNCur->Value=Value;
	JNCur->Type=JOT_Float;
}
void Json_SetObj(JSON_Node *JNCur,uint8 *Option,void *Value)
{
	JNCur->Option=Option;
	JNCur->Value=Value;
	JNCur->Type=JOT_Obj;
}
void Json_NodeToString(JSON_Node *JNCur,uint8 *P)
{
	StringEndingAppend(JNCur->Option,P);
	StringEndingAppend(":",P);
	switch(JNCur->Type)
	{
		case JOT_String:StringEndingAppend(JNCur->Value,P);break;
		case JOT_Int:break;
		case JOT_Node:StringEndingAppend("{",P);Json_NodeToString(JNCur->Next,P);break;
	}
	StringEndingAppend("}",P);
}
uint8 *Json_ToString(JSON_Node *JNCur)
{
	uint8 *P;
	JSON_Node *JNP;
	P=Mema_Malloc(44);
	JNP=JNCur;
	StringCoppy("{",P);
	Json_NodeToString(JNP,P);
	return P;
}
void Json_String_Clear(void *Str)
{
	Mema_Free(Str);
}
void Json_Clear(JSON_Node *JNCur)
{
	
}



///以下代码参考网上

JSONNode *newJSONNode(){  
    JSONNode *node =(JSONNode *)Mema_Malloc(sizeof(JSONNode));  
    return node;  
}  
 
JSONObjectNode *newJSONObjectNode(){  
    JSONObjectNode *node =(JSONObjectNode *)Mema_Malloc(sizeof(JSONObjectNode));  
    return node;  
}


JSONList *initLinkList(){  
	JSONList *ret =(JSONList *)Mema_Malloc(sizeof(JSONList));  
	ret->start = NULL;  
	ret->end = NULL;  
	ret->length = 0;  
	return ret;  
}  

void initJSONNode(JSONNode *node, char *key, char *value, int type){  
	node->key = key;  
	node->value = value;  
	node->keyLength = GetTextLength(key);  
	node->valueLength = GetTextLength(value);  
	node->type = type;  
}  

/** 
* 添加一个普通JSON键值对 
*/  
void addNode(JSONList *list, char *key, char *value){  
				
JSONNode *node = NULL;  
	node = newJSONNode();  
	if(list->length == 0){  
			node->next = NULL;  
			node->prev = NULL;  
			list->start = node;  
			list->end = node;  
	}else{  
			node->next = NULL;  
			node->prev = list->end;  
			list->end->next = node;  
			list->end = node;  
	}  
	list->length++;  
				
	node->type = JSONTYPE_KV;  
	node->keyLength = GetTextLength(key);  
	node->valueLength = GetTextLength(value);  
	node->key = key;  
	node->value = value;  
}  

/** 
* 添加一个JSON Array键值对 
*/  
void addJSONArray(JSONList *list, char *key, JSONObjectNode **value, int length){  
	JSONNode *node = NULL;  
	JSONNode *indexNode = list->start;  
	int sameKeyFlag = 0;  
	while(indexNode != NULL){       //遍历查看是否已经有这个键  
	int cmp = CompareWithString((uint8 *)indexNode->key, (uint8 *)key);  
	if(cmp == 0){  
			sameKeyFlag = 1;  
			node = indexNode;       //如果存在，直接获取节点  
			 break;  
	}  
	indexNode = indexNode->next;  
	}  
				
	if(sameKeyFlag == 0){          //如果不存在，创建一个节点加入链表  
								
	node = newJSONNode();  
						
	node->arrayLength = -1;  
						
	if(list->length == 0){  
			node->next = NULL;  
			node->prev = NULL;  
			list->start = node;  
			list->end = node;  
	}else{  
			node->next = NULL;  
			node->prev = list->end;  
			list->end->next = node;  
			list->end = node;  
	}  
	list->length++;  
	}  
				
	node->type = JSONTYPE_ARR;  
	node->keyLength = GetTextLength(key);  
	//node->valueLength = GetTextLength(value);  
	node->key = key;  
	//node->array[node->arrayIndex] = value;  
	//node->arrayIndex++;  
	node->value = NULL;  
	node->valueLength = 0;  
				
	node->objectNode = value;  
	node->arrayLength = length;  
}  

/** 
* 将普通jsonNode转换为字符串的形式 
*/  
char *getJSONObjString(char *mem, int *index, JSONNode *nodePtr){  

			char *str = NULL;  
		
			mem[(*index)++] = '"';  
			BufferCoppy(mem+(*index), nodePtr->key, nodePtr->keyLength);  
			*index = *index + nodePtr->keyLength;  
			mem[(*index)++] = '"';     
		
			mem[(*index)++] = ':';  
				
			BufferCoppy(mem+(*index), nodePtr->value, nodePtr->valueLength);  
			*index = *index + nodePtr->valueLength;  
		
			mem[(*index)] = '\0';  
			str = mem;  
			return str;  
}  

/** 
* 将json数组转换为字符串，如果嵌套了数组则会递归转换 
*/  
char *getJSONArrayString(char *mem, int *index, JSONNode *nodePtr){  
	char *str = NULL;  
	int i,j;  
	int length = nodePtr->arrayLength;  
	int type;  
		
	mem[(*index)++] = '"';  
	BufferCoppy(mem+(*index), nodePtr->key, nodePtr->keyLength);  
	*index = *index + nodePtr->keyLength;  
	mem[(*index)++] = '"';  
	mem[(*index)++] = ':';  
		
	if(length > 0){  
			mem[(*index)++] = '[';  
			for(i=0; i<length; i++){  
												
					JSONObjectNode *objectNode;  
												
					if(i == 0){  
							 objectNode = nodePtr->objectNode[i];  
					}else{  
					objectNode = objectNode->next;  
	}  
	mem[(*index)++] = '{';  
										
 for(j=0; j<objectNode->length; j++){  
																
		 type = objectNode->jsonNode[j]->type;  
		 if(type == JSONTYPE_KV){  
		 getJSONObjString((mem), index, objectNode->jsonNode[j]);  
 }else if(type == JSONTYPE_ARR){  
			getJSONArrayString((mem), index, objectNode->jsonNode[j]);  
 }  
 mem[(*index)++] = ',';  
 }  
										
 mem[(*index)-1] = '}';  
 if(i < nodePtr->arrayLength-1){  
		 mem[(*index)++] = ',';  
 }  
 }  
 mem[(*index)++] = ']';  
 }  
 mem[(*index)] = '\0';  
 str = mem;  
 return str;  
}  

/** 
* 转换主干JSON列表为字符串 
*/  
char *getJsonString(JSONNode **start, int length){  
				
	int i;   
	JSONNode *nodePtr = *start;  
	char *jsonStr = Mema_Malloc(256);  
		
	int index = 0;  
	jsonStr[0] = '{';  
	index++;  
	for(i=0; i<length; i++){  
			if(nodePtr != NULL){  
														
					if(nodePtr->type == JSONTYPE_KV){  
							getJSONObjString(jsonStr, &index, nodePtr);  
					}else if(nodePtr->type == JSONTYPE_ARR){  
							getJSONArrayString(jsonStr, &index, nodePtr);  
			}  
	jsonStr[index] = ',';  
	index++;  
	}  
	nodePtr = nodePtr->next;  
	}  
	jsonStr[index-1] = '}';  
	jsonStr[index] = '\0';  

	return jsonStr;  
}  
