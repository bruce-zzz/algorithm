#ifndef LRU_CHACHE_H
#define LRU_CHACHE_H
#include <unordered_map>
#include "DoubleLink.h"

namespace domain_algorithm_share {

	template<class Tk,	// key type
		class Tv	// mapped type
	>
	struct KeyValue
	{
		Tk key;
		Tv value;
	};

	template<class Tk,	// key type
		class Tv	// mapped type
	>
	class LRUCache
	{


	public:
		LRUCache(int capacity);

		~LRUCache();

		Tv Get(const Tk &key);

		void Put(const Tk &key, const Tv &val);


	private:

		int m_Capacity;
		DoubleLink<KeyValue<Tk, Tv> > m_Cache;
		std::unordered_map<Tk, DNode<KeyValue<Tk, Tv> > *>m_KeyToNode;
	};

	template<class Tk,	// key type
		class Tv	// mapped type
	>
	LRUCache<Tk, Tv>::LRUCache(int capacity) :m_Capacity(capacity), m_KeyToNode(capacity) {
	}

	template<class Tk,	// key type
		class Tv	// mapped type
	>
	LRUCache<Tk, Tv>::~LRUCache() {

	}

	template<class Tk,	// key type
		class Tv	// mapped type
	>
	Tv LRUCache<Tk, Tv>::Get(const Tk &key) {
		typename std::unordered_map<Tk, DNode<KeyValue<Tk, Tv> >* >::iterator iter = m_KeyToNode.find(key);
		if (iter == m_KeyToNode.end()) {//map�в�����key ֱ�ӷ���-1
			//ģ�淽�������ڷ�int���ͣ���Ҫ��������Ϊ����Ӧ���⣬���÷���-1
			return -1;
		}

		Put(key, iter->second->value.value);// ���� put �����Ѹ�������ǰ
		return iter->second->value.value;
	}

	template<class Tk,	// key type
		class Tv	// mapped type
	>
	void LRUCache<Tk, Tv>::Put(const Tk &key, const Tv &val) {
		KeyValue<Tk, Tv> keyValue;
		keyValue.key = key;
		keyValue.value = val;
		typename std::unordered_map<Tk, DNode<KeyValue<Tk, Tv> > *>::iterator iter = m_KeyToNode.find(key);
		if (iter != m_KeyToNode.end()) {//map�д���key
			m_Cache.delete_node(iter->second);//˫��������ɾ�� map�д������ڵ�
			m_Cache.insert_first(keyValue);//˫����������key����ֵ�洢
			m_KeyToNode[key] = m_Cache.get_first();//map�и������key��Ӧ����ֵ
		}
		else {
			if (m_Capacity == m_Cache.size()) {//�ﵽ��������
				m_KeyToNode.erase(m_Cache.get_last()->value.key);//map��ɾ��˫�������б�β��ֵ ��Ӧ��key
				m_Cache.delete_last();//ͬʱ˫������ɾ����β��ֵ
			}
			m_Cache.insert_first(keyValue);//˫������������ݲ����ͷ 
			m_KeyToNode[key] = m_Cache.get_first();//map��Ӧֵ���и���
		}
	}

}
#endif