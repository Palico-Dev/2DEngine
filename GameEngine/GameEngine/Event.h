// Written by Andy Wang
#pragma once

#ifndef _EVENT_H_
#define _EVENT_H_

#include <functional>
#include <map>
#include <set>

typedef unsigned int con_id;

template <typename... T>
class Event {
	typedef std::function<void(T...)> callback;

	con_id* const idCounter = NULL;
	std::map<con_id, callback>* const connections = NULL;
	std::set<con_id>* const onceConnections = NULL;  // this should always be a subset of connections

public:
	// constructor allocates necessary pointers
	Event() :
		idCounter(new con_id(0)),
		connections(new std::map<con_id, callback>()),
		onceConnections(new std::set<con_id>()) {}

	// destructor deletes them
	// precondition: the pointers should exist since they are never deleted earlier
	~Event() {
		delete idCounter;
		delete connections;
		delete onceConnections;
	}

	// connect a callback
	con_id Connect(callback cb) const {
		con_id id = GetConId();
		connections->emplace(id, cb);
		return id;
	}

	// connect a once callback; automatically gets disconnected after getting fired
	con_id Once(callback cb) const {
		con_id id = GetConId();
		connections->emplace(id, cb);
		onceConnections->insert(id);
#ifdef _DEBUG
		AssertOnceConnectionsIsSubset();
#endif
		return id;
	}

	// disconnect a connection given its id
	void Disconnect(con_id id) const {
		connections->erase(id);
		onceConnections->erase(id);
#ifdef _DEBUG
		AssertOnceConnectionsIsSubset();
#endif
	}

	// disconnect all connections
	void DisconnectAll() const {
		connections->clear();
		onceConnections->clear();
	}

	// fire all connections
	void Fire(T...) const;

private:
	// delete copy constructor
	Event(Event&) = delete;

	// helper function to increment and return connection id
	con_id GetConId() const { return ++(*idCounter); }

	// test that onceConnections is a subset of connections
#ifdef _DEBUG
	void AssertOnceConnectionsIsSubset() const {
		for (auto it = onceConnections->begin(); it != onceConnections->end(); ++it) {
			assert(connections->count(*it) == 1);
		}
	}
#endif
};

template <typename... T>
inline void Event<T...>::Fire(T... args) const {
#ifdef _DEBUG
	AssertOnceConnectionsIsSubset();  // assert that all once callbacks WILL be called
#endif
	for (auto it = connections->begin(); it != connections->end(); ++it) {
		it->second(args...);
	}
	// remove once connections
	for (auto it = onceConnections->begin(); it != onceConnections->end(); ++it) {
		connections->erase(*it);
	}
	onceConnections->clear();
}

#endif