// _  __                   _         _        ____         _   
//| |/ / ___   ___  _ __  (_)  __ _ ( ) ___  / ___|   ___ | |_ 
//| ' / / __| / _ \| '_ \ | | / _` ||/ / __| \___ \  / _ \| __|
//| . \ \__ \|  __/| | | || || (_| |   \__ \  ___) ||  __/| |_ 
//|_|\_\|___/ \___||_| |_||_| \__,_|   |___/ |____/  \___| \__|
//                                                            
#define _GLIBCXX_DEBUG
#include<iostream>
#include<random>
using namespace std;
std::mt19937_64 rnd(65537);

template <typename T>
struct Node {
	T val;
	uint64_t prior;
	Node<T>* l;
	Node<T>* r;
	Node(T value) : val{value}, prior(rnd()), l(nullptr), r(nullptr) {}
	//Node() : val{0}, prior{0} {}
};

template <typename T>
pair<Node<T>*,Node<T>*> splitl(Node<T>* v,T key) {
	if(!v)
		return {nullptr,nullptr};
	if(key<=v->val) {
		auto s = splitl(v->l, key);
		v->l=s.second;
		return {s.first,v};
	}
	else {
		auto s = splitl(v->r, key);
		v->r=s.first;
		return {v,s.second};
	}
}

template <typename T>
pair<Node<T>*,Node<T>*> splitr(Node<T>* v,T key) {
	if(!v)
		return {nullptr,nullptr};
	if(key<v->val) {
		auto s = splitr(v->l, key);
		v->l=s.second;
		return {s.first,v};
	}
	else {
		auto s = splitr(v->r, key);
		v->r=s.first;
		return {v,s.second};
	}
}

template <typename T>
Node<T>* merge(Node<T>* l,Node<T>* r) {
	if(!l)
		return r;
	if(!r)
		return l;
	if(l->prior > r->prior) {
		l->r=merge(l->r,r);
		return l;
	}
	else {
		r->l=merge(l,r->l);
		return r;
	}
}

template <typename T>
size_t clear_tree(Node<T>* root) {
	size_t ans=1;
	if(!root) {
		return 0;
	}
	ans+=clear_tree(root->l);
	ans+=clear_tree(root->r);
	delete(root);
	return ans;
}

template <typename T>
bool search(Node<T>* v,T key) {
	if(!v) {
		return false;
	}
	if(v->val==key) {
		return true;
	}
	if(v->val > key) {
		return search(v->l,key);
	}
	return search(v->r,key);
}

template <typename T>
void print_tree(Node<T>* v) {
	if(!v) {
		return;
	}
	cout<<v->val<<"(";
	print_tree(v->l);
	cout<<")[";
	print_tree(v->r);
	cout<<"]";
}

template <typename T>
struct Set {
	Node<T>* root;
	size_t size;
	Set() : 
		root {nullptr},
		size{0} {}
	//T operator[](uint32_t i) const {
	//	return elements[i];
	//}
	bool empty() const {
		return size==0;
	}
	bool contains(T key) const {
		return search(root,key);
	}
	void insert(T element) {
		if(this->contains(element)) {
			return;
		}
		Node<T>* v=new Node<T>(element);
		auto s1=splitl(root, element);
		root=merge(merge(s1.first,v),s1.second);
		++size;
	}
	void clear() {
		size=0;
		clear_tree(root);
		root=nullptr;
	}
	void erase(T key) {
		if(!this->contains(key)) {
			return;
		}
		auto s1=splitl(root,key);
		auto s2=splitr(s1.second,key);
		size--;
		root=merge(s1.first,s2.second);
	}
	T example() const {
		return root->val;
	}
};

template <typename T>
Set<T> set_new() {
	return Set<T>();
}

template <typename T>
void set_insert(Set<T>& st,T val) {
	st.insert(val);
}

template <typename T>
void set_remove(Set<T>& st,T val) {
	st.erase(val);
}

template <typename T>
bool set_is_empty(Set<T> const& set) {
	return set.empty();
}

template <typename T>
T set_example(Set<T> const& set) {
	return set.example();
}

template <typename T>
bool set_contains(Set<T> const& set, T key) {
	return set.contains(key);
}

template <typename T>
void set_erase(Set<T>& st) {
	st.clear();
}

int main() {
	Set<int> st=set_new<int>();
	string s;
	int x;
	while(cin>>s) {
		if(s=="insert") {
			cin>>x;
			set_insert(st,x);
		} else if(s=="remove") {
			cin>>x;
			set_remove(st,x);
		} else if(s=="contains") {
			cin>>x;
			cout<<(set_contains(st,x) ? "true" : "false") << '\n';
		} else if(s=="empty") {
			cout<<(set_is_empty(st) ? "true" : "false") << '\n';
		} else if(s=="erase") {
			set_erase(st);
		} else if(s=="example") {
			cout<<set_example(st) << '\n';
		} else {
			cout<<"bad command:"<<s<<' '<<x<<'\n';
		}
	}
	return 0;
}
