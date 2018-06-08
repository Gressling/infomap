/*
 * InfomapIterator.h
 *
 */

#ifndef INFOMAP_ITERATOR_H_
#define INFOMAP_ITERATOR_H_

#include <deque>

namespace infomap {

class InfoNode;

/**
 * Pre processing depth first iterator that explores sub-Infomap instances
 * Note:
 * This iterator presupposes that the next pointer of a node can't reach a node with a different parent.
 */
class InfomapIterator
{
protected:
	InfoNode* m_root = nullptr;
	InfoNode* m_current = nullptr;
	int m_moduleIndexLevel = -1;
	unsigned int m_moduleIndex = 0;
	std::deque<unsigned int> m_path; // The child index path to current node
	unsigned int m_depth = 0;

public:

	InfomapIterator() {}

	InfomapIterator(InfoNode* nodePointer, int moduleIndexLevel = -1)
	:	m_root(nodePointer),
		m_current(nodePointer),
		m_moduleIndexLevel(moduleIndexLevel)
	{}

	InfomapIterator(const InfomapIterator& other)
	:	m_root(other.m_root),
		m_current(other.m_current),
		m_moduleIndexLevel(other.m_moduleIndexLevel),
		m_moduleIndex(other.m_moduleIndex),
		m_path(other.m_path),
		m_depth(other.m_depth)
	{}

	virtual ~InfomapIterator() {}

	InfomapIterator& operator= (const InfomapIterator& other)
	{
		m_root = other.m_root;
		m_current = other.m_current;
		m_moduleIndexLevel = other.m_moduleIndexLevel;
		m_moduleIndex = other.m_moduleIndex;
		m_path = other.m_path;
		m_depth = other.m_depth;
		return *this;
	}

	InfoNode* current()
	{
		return m_current;
	}

	const InfoNode* current() const
	{
		return m_current;
	}

	InfoNode* operator->()
	{
		return m_current;
	}

	const InfoNode* operator->() const
	{
		return m_current;
	}

	// InfoNode& operator*();

	virtual InfomapIterator& operator++();

	virtual InfomapIterator operator++(int)
	{
		InfomapIterator copy(*this);
		++(*this);
		return copy;
	}

	virtual InfomapIterator& stepForward()
	{
		++(*this);
		return *this;
	}

	const std::deque<unsigned int>& path() const
	{
		return m_path;
	}

	unsigned int moduleIndex() const
	{
		return m_moduleIndex;
	}

	unsigned int depth() const
	{
		return m_depth;
	}

	bool isEnd() const
	{
		return m_current == nullptr;
	}
};

class InfomapLeafModuleIterator : public InfomapIterator
{
public:
	InfomapLeafModuleIterator() { init(); }

	InfomapLeafModuleIterator(InfoNode* nodePointer, int moduleIndexLevel = -1)
	:	InfomapIterator(nodePointer, moduleIndexLevel)
	{ init(); }

	InfomapLeafModuleIterator(const InfomapLeafModuleIterator& other)
	:	InfomapIterator(other)
	{ init(); }

	/**
	 * Iterate to first leaf module
	 */
	void init();

	virtual InfomapIterator& operator++();

	virtual InfomapIterator operator++(int)
	{
		InfomapLeafModuleIterator copy(*this);
		++(*this);
		return copy;
	}

};

class InfomapLeafIterator : public InfomapIterator
{
public:
	InfomapLeafIterator() { init(); }

	InfomapLeafIterator(InfoNode* nodePointer, int moduleIndexLevel = -1)
	:	InfomapIterator(nodePointer, moduleIndexLevel)
	{ init(); }

	InfomapLeafIterator(const InfomapLeafIterator& other)
	:	InfomapIterator(other)
	{ init(); }

	/**
	 * Iterate to first leaf module
	 */
	void init();

	virtual InfomapIterator& operator++();

	virtual InfomapIterator operator++(int)
	{
		InfomapLeafIterator copy(*this);
		++(*this);
		return copy;
	}

};

}

#endif /* INFOMAP_ITERATOR_H_ */
