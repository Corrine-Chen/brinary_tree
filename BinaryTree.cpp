#include<iostream>
using namespace std;
#include<queue>
#include<stack>

template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& data)
		: _data(data)
		, _pLeft(NULL)
		, _pRight(NULL)
	{}

	T _data;
	BinaryTreeNode<T>* _pLeft;    // 左孩子
	BinaryTreeNode<T>* _pRight;   // 右孩子
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		: _pRoot(NULL)
	{}


	BinaryTree(const T array[], size_t size, const T& invalid)
	{
		// 创建树
		size_t index = 0;
		_CreateTree(_pRoot, array, size, index, invalid);
	}

	BinaryTree(const BinaryTree<T>& t)
	{
		_pRoot = _CopyBinaryTree(t._pRoot);
	}

	BinaryTree<T>& operator=( BinaryTree<T>& t)
	{
		if(this != &t)
		{
			std::swap(_pRoot,t._pRoot);
		}
		return *this;
	}

	// 先序遍历
	void PreOrder()
	{
		cout<<"PreOrder:"<<" ";
		_PreOrder(_pRoot);
		cout<<endl;
	}

	// 中序遍历：访问左子树-->根-->右子树 
	void InOrder()
	{
		cout<<"InOrder:"<<" ";
		_InOrder(_pRoot);
		cout<<endl;
	}

	// 后续遍历：访问左子树-->访问右子树-->访问根节点
	void PostOrder()
	{
		cout<<"PostOrder:"<<" ";
		_PostOrder(_pRoot);
		cout<<endl;
	}

	// 层序遍历
	void LevelOrder()
	{
		cout<<"LevelOrder:"<<" ";
		_LevelOrder(_pRoot);
		cout<<endl;
	}

	void PreOrder_Nor()//非递归前序遍历
	{
		cout<<"PreOrder_Nor:"<<" ";
		_PreOrder_Nor(_pRoot);
		cout<<endl;
	}

	void InOrder_Nor()//非递归中序遍历
	{
		cout<<"InOrder_Nor:"<<" ";
		_InOrder_Nor(_pRoot);
		cout<<endl;
	}


	Node* GetParent(Node* x)//得到一个节点的双亲节点
	{
		return _GetParent(_pRoot, x);
	}

	Node* Find(const T& value)//寻找节点
	{
		return _Find(_pRoot, value);
	}

	Node* GetLeftChild(Node* pCur)//得到一个节点的左孩子
	{
		return pCur->_pLeft;
	}
	Node* GetRightChild(Node* pCur)//得到一个节点的右孩子
	{
		return pCur->_pRight;
	}

	size_t Height()//得到树的高度
	{
		return _Height(_pRoot);
	}

	size_t GetLeefNode()//得到叶子节点的数目
	{
		return _GetLeefNode(_pRoot);
	}

	size_t GetKLevelNode(size_t k)//得到第k层节点的个数
	{
		return _GetKLevelNode(_pRoot, k);
	}

	 // 后续遍历的非递归版本
	void PostOrder_Nor()
	{
		Node* pCur = _pRoot;
		stack<Node*> s; 
		cout<<"PostOrder_Nor"<<" ";
		int flag[100]={0};//标记队列中第size个元素是否被访问
		s.push(pCur);
		while(!s.empty())
		{
			while(pCur->_pLeft)//找到根结点的最右节点，并把访问过的节点都保存到栈中；
			{
				if(flag[s.size()]==1 && pCur->_pRight!= NULL)
				{
					pCur=pCur->_pRight;
					s.push(pCur);
				}
				else
				{
					pCur = pCur->_pLeft;
					s.push(pCur);
				}
			}
			pCur = s.top();


			while(NULL==pCur->_pRight && !s.empty())
			{
				cout<<pCur->_data<<" ";
				s.pop();
				pCur = s.top();
			}
			pCur = s.top();
			while(flag[s.size()]==1 && !s.empty())
			{
				pCur = s.top();
				cout<<pCur->_data<<" ";
				s.pop();
			}
			flag[s.size()]=1;
		}
	}
	 // 求二叉树的镜像：非递归
	void GetBinaryMirror_Nor()
	{
		if(NULL==_pRoot)
			return ;
		
		queue<Node*> q;
		Node* pCur=_pRoot;
		q.push(pCur);
		while(!q.empty())
		{
			while(pCur->_pLeft || pCur->_pRight)
			{
				pCur=q.front();
				std::swap(pCur->_pLeft,pCur->_pRight);
				q.pop();
				if(pCur->_pLeft)
				{
					q.push(pCur->_pLeft);
				}
				if(pCur->_pRight)
				{
					q.push(pCur->_pRight);
				}
			}
			q.pop();
		}
	}

	  // 求二叉树的镜像：递归版本
	void GetBinaryMirror()
	{
		return _GetBinaryMirror(_pRoot);
	}


	// 利用层序遍历来处理--> 关键：找第一个度不为2的结点-->后续结点
	// 如果有孩子则不是完全二叉树
	// 否则：是
	bool IsCompleteBinaryTree()
	{
		queue<Node*> q;
		Node* pCur=_pRoot;
		q.push(pCur);
		bool IsLeftflag=false;
		while(!q.empty())
		{
			pCur=q.front();
			if(pCur->_pRight&& pCur->_pLeft && false == IsLeftflag)
			{
				q.push(pCur->_pLeft);
				q.push(pCur->_pRight);
				q.pop();
			}
			else if(pCur->_pLeft)
			{
				q.push(pCur->_pLeft);
				IsLeftflag=true;
				q.pop();
			}
			else if(pCur->_pRight)
			{
				return false;
			}
			else
			{
				IsLeftflag=true;
				q.pop();
			}
		}
		return true;
	}

	~BinaryTree()
	{
		_DestroyTree(_pRoot);
	}

private:
	void _CreateTree(Node*& pRoot, const T array[], size_t size, size_t& index, const T& invalid)
	{

		if(index < size && array[index] != invalid)
		{
			pRoot=new Node(array[index]);
			_CreateTree(pRoot->_pLeft,array, size, ++index, invalid);
			_CreateTree(pRoot->_pRight,array, size, ++index, invalid);
		}

	}

	Node* _CopyBinaryTree(Node* pRoot)
	{
		if(pRoot==NULL)
		{
			return NULL;
		}
		Node* NewpRoot=NULL;
		NewpRoot = new BinaryTreeNode<T>(pRoot->_data);
		NewpRoot->_pLeft=_CopyBinaryTree(pRoot->_pLeft);
		NewpRoot->_pRight=_CopyBinaryTree(pRoot->_pRight);

		return NewpRoot;
	}

	void _DestroyTree(Node* &pRoot)
	{
		Node* temp = pRoot;
		if(pRoot==NULL)//根节点为空  则不需要delete   直接return
			return;
		_DestroyTree(temp->_pLeft);
		_DestroyTree(temp->_pRight);
		delete temp;
		temp=NULL;
	}

	void _PreOrder(Node* pRoot)
	{
		Node* temp=pRoot;
		if(temp==NULL)
			return ;
		cout<<temp->_data<<" ";

		_PreOrder(temp->_pLeft);
		_PreOrder(temp->_pRight);
	}

	void _InOrder(Node* pRoot)
	{
		Node* temp=pRoot;
		if(temp==NULL)
			return ;

		_InOrder(temp->_pLeft);
			cout<<temp->_data<<" ";
		_InOrder(temp->_pRight);
	}

	void _PostOrder(Node* pRoot)
	{
		Node* temp=pRoot;
		if(temp==NULL)
			return ;

		_PostOrder(temp->_pLeft);
		_PostOrder(temp->_pRight);
		cout<<temp->_data<<" ";
	}
	void _LevelOrder(Node* pRoot)
	{
		Node *tmp = _pRoot;  
        queue<Node*> q;  
		q.push(tmp);  
		while (!q.empty())  
		{  
			Node* top = q.front();  
			q.pop();  
			cout << top->_data << " ";  
			if (top->_pLeft)  
			{  
				q.push(top->_pLeft);  
			}  
			if (top->_pRight)  
			{  
				q.push(top->_pRight);  
			}  
		}  
	}

	void _PreOrder_Nor(Node* pRoot)
	{
		if(pRoot==NULL)
			return ;
		stack<Node*> s;
		s.push(pRoot);
		while(!s.empty())
		{
			Node* t=s.top();
			cout<<t->_data<<" ";
			s.pop();

			if(NULL!=t->_pRight)
				s.push(t->_pRight);

			if(NULL!=t->_pLeft)
				s.push(t->_pLeft);

		}

	}
	void _InOrder_Nor(Node* pRoot)
	{
		if(NULL== pRoot)
			return;
		Node* pCur = pRoot;
		stack<Node*> s;
		while(pCur || !s.empty())
		{
			while(pCur)
			{
				s.push(pCur);
				pCur = pCur->_pLeft;
			}
			Node* t=s.top();
			cout<<t->_data<<" ";
			s.pop();

			pCur=t->_pRight;
		}
	}

	Node* _GetParent(Node* pRoot, Node* x)
	{
		if(x == pRoot || NULL == x || NULL == pRoot)
			return NULL;

		if(x == pRoot->_pLeft || x == pRoot->_pRight)
			return pRoot;

		if(x!=pRoot)
		{
			_GetParent(pRoot->_pLeft,x);
			_GetParent(pRoot->_pRight,x);
		}
	}

	Node* _Find(Node* pRoot, const T& value)
	{
		Node* ret=NULL;
		Node* pCur = pRoot;
		if(NULL==pCur)
			return NULL;
		if(value==pCur->_data)
		{
			ret=pCur;
		}
		else
		{
			ret=_Find(pCur->_pLeft,value);
			if(ret==NULL)
			{
				ret=_Find(pCur->_pRight,value);
			}
		}
		return ret;
	}

	size_t _Height(Node* pRoot)
	{
		if(NULL == pRoot)
			return 0;
		if(NULL==pRoot->_pLeft && NULL==pRoot->_pRight)
			return 1;
		else
		{
			return _Height(pRoot->_pLeft) > _Height(pRoot->_pRight) ?  _Height(pRoot->_pLeft)+1:_Height(pRoot->_pRight)+1;
		}
	}

	size_t _GetLeefNode(Node* pRoot)
	{
		if(pRoot==NULL)
			return 0;
		if(pRoot->_pLeft==NULL && NULL==pRoot->_pRight)
			return 1;
		else
		{
			return _GetLeefNode(pRoot->_pLeft)+_GetLeefNode(pRoot->_pRight);
		}
	}

	size_t _GetKLevelNode(Node* pRoot, size_t k)
	{
		if(pRoot==NULL || k<1 || k>Height())
			return 0;
		if(k==1)
			return 1;
		else
		{
			return _GetKLevelNode(pRoot->_pLeft,k-1)+_GetKLevelNode(pRoot->_pRight,k-1);
		}
	}

	void _GetBinaryMirror(Node* pRoot)
	{
		if(NULL == pRoot)
			return;

		std::swap(pRoot->_pLeft,pRoot->_pRight);

		
		_GetBinaryMirror(pRoot->_pLeft);
	
		_GetBinaryMirror(pRoot->_pRight);
		
		return;
		
	}



private:
	BinaryTreeNode<T>* _pRoot;
};



void Funtest()
{
	char* array={"124###35##6"};
	/*BinaryTree <char>Node(array,strlen(array),'#');
	BinaryTree <char>Node1(Node);
	BinaryTree <char>Node2;
	Node2 = Node;*/
	BinaryTree <char> t(array,strlen(array),'#');
	t.PreOrder();
	t.InOrder();
	t.PostOrder();
	t.LevelOrder();

}

void FunTest1()
{
	char* array={"124###35##6"};
	BinaryTree <char> t(array,strlen(array),'#');
	t.PreOrder_Nor();
	t.PreOrder();
	t.InOrder();
	t.InOrder_Nor();
	BinaryTreeNode <char>* Node=NULL;
	BinaryTreeNode<char>* x= t.Find('5');
	Node=t.GetParent(x);
	cout<<"Parent: ";
	cout<<Node->_data<<" ";
	cout<<endl;

	size_t ret = t.Height();
	cout<<"Height: ";
	cout<<ret<<endl;

	ret = t.GetLeefNode();
	cout<<"GetLeefNode: ";
	cout<<ret<<endl;

	ret = t.GetKLevelNode(2);
	cout<<"GetKLevelNode: ";
	cout<<ret<<endl;


	x= t.Find('3');
	Node=t.GetLeftChild(x);
	cout<<"LeftChild:";
	cout<<Node->_data<<endl;

	Node=t.GetRightChild(x);
	cout<<"RightChild:";
	cout<<Node->_data<<endl;

}

void FunTest2()
{
	char* array={"124###35##6"};
	BinaryTree <char> t(array,strlen(array),'#');
	t.PostOrder();
	t.PostOrder_Nor();
	cout<<endl;

	t.GetBinaryMirror_Nor ();

	char* array1={"124##7##35##6"};
	BinaryTree <char> a(array1,strlen(array1),'#');

	a.GetBinaryMirror();
	cout<<a.IsCompleteBinaryTree ()<<endl;


}

int main()
{
	Funtest();
	//FunTest1();
	//FunTest2();
	system("pause");
	return 0;
}