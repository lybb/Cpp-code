//把二叉树打印成多行
//思路分析：层序遍历的思想，但是是要打印成多行，就要一个计数器来统计每行元素的个数
//这里使用一个队列，按照层序遍历的结果将结点放入队列中，队列中的元素始终保持只有一
//层的元素

vector<vector<int> > Print(TreeNode* pRoot) {

	vector<vector<int>> ret;
	if(pRoot == NULL)
		return ret;

	queue<TreeNode*> q;
	q.push(pRoot);

	while(!q.empty()){
		vector<int> v;
		size_t sz = q.size();	//该层元素的个数
		while(sz--){	//以sz来定边界进行每层元素的存储
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

//二叉树的下一个结点（按照中序遍历的顺序，并且该二叉树采用三叉链的方式存储）
//思路分析：查找二叉树的下一个结点时，需要分一下三种情况查找。假设传入的结点是pNode
//1.pNode有右子树：该情况下pNode下一个结点是其右子树的最左结点；
//2.没有右子树，且是其父节点的左结点时：此时pNode的下一个结点是其父节点
//3.没有右子树，且是其父节点的右结点时：这种情况下，就要沿着parent指针向上遍历，直到
//找到某一个结点不是它父节点的右子节点时，其父节点就是pNode的下一个结点
TreeLinkNode* GetNext(TreeLinkNode* pNode)
{
	if(pNode == NULL)
		return NULL;

	TreeLinkNode* pNext = NULL;
	if(pNode->right != NULL){    //pNode有右子树，则找右子树中的最左结点
		TreeLinkNode* pRLeft = pNode->right;
		while(pRLeft->left != NULL){
			pRLeft = pRLeft->left;
		}
		pNext = pRLeft;
	}else if(pNode->next != NULL){       //pNode没有右子树
		TreeLinkNode* pCur = pNode;
		TreeLinkNode* pParent = pNode->next;
		//没有右子树且是其父节点的有结点，则向上遍历，直到找到不是其父节点的右结点的结点
		while(pParent!=NULL && pCur==pParent->right){  
			pCur = pParent;
			pParent = pParent->next;
		}
		pNext = pParent;
	}

	return pNext;
}