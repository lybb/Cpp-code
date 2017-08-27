//�Ѷ�������ӡ�ɶ���
//˼·���������������˼�룬������Ҫ��ӡ�ɶ��У���Ҫһ����������ͳ��ÿ��Ԫ�صĸ���
//����ʹ��һ�����У����ղ�������Ľ��������������У������е�Ԫ��ʼ�ձ���ֻ��һ
//���Ԫ��

vector<vector<int> > Print(TreeNode* pRoot) {

	vector<vector<int>> ret;
	if(pRoot == NULL)
		return ret;

	queue<TreeNode*> q;
	q.push(pRoot);

	while(!q.empty()){
		vector<int> v;
		size_t sz = q.size();	//�ò�Ԫ�صĸ���
		while(sz--){	//��sz�����߽����ÿ��Ԫ�صĴ洢
			TreeNode* Front = q.front();
			v.push_back(Front->val);
			q.pop();

			if(Front->left)
				q.push(Front->left);
			if(Front->right)
				q.push(Front->right);
		}
		ret.push_back(v);
	}
	return ret;
}

//����������һ����㣨�������������˳�򣬲��Ҹö����������������ķ�ʽ�洢��
//˼·���������Ҷ���������һ�����ʱ����Ҫ��һ������������ҡ����贫��Ľ����pNode
//1.pNode�����������������pNode��һ����������������������㣻
//2.û���������������丸�ڵ������ʱ����ʱpNode����һ��������丸�ڵ�
//3.û���������������丸�ڵ���ҽ��ʱ����������£���Ҫ����parentָ�����ϱ�����ֱ��
//�ҵ�ĳһ����㲻�������ڵ�����ӽڵ�ʱ���丸�ڵ����pNode����һ�����
TreeLinkNode* GetNext(TreeLinkNode* pNode)
{
	if(pNode == NULL)
		return NULL;

	TreeLinkNode* pNext = NULL;
	if(pNode->right != NULL){    //pNode���������������������е�������
		TreeLinkNode* pRLeft = pNode->right;
		while(pRLeft->left != NULL){
			pRLeft = pRLeft->left;
		}
		pNext = pRLeft;
	}else if(pNode->next != NULL){       //pNodeû��������
		TreeLinkNode* pCur = pNode;
		TreeLinkNode* pParent = pNode->next;
		//û�������������丸�ڵ���н�㣬�����ϱ�����ֱ���ҵ������丸�ڵ���ҽ��Ľ��
		while(pParent!=NULL && pCur==pParent->right){  
			pCur = pParent;
			pParent = pParent->next;
		}
		pNext = pParent;
	}

	return pNext;
}