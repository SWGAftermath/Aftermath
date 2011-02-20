/*
 *	server/zone/objects/tangible/fishing/FishObject.cpp generated by engine3 IDL compiler 0.60
 */

#include "FishObject.h"

#include "server/zone/objects/scene/SceneObject.h"

#include "server/zone/Zone.h"

#include "server/zone/packets/scene/AttributeListMessage.h"

#include "server/zone/packets/object/ObjectMenuResponse.h"

#include "server/zone/objects/player/PlayerCreature.h"

#include "server/zone/ZoneServer.h"

/*
 *	FishObjectStub
 */

FishObject::FishObject() : TangibleObject(DummyConstructorParameter::instance()) {
	FishObjectImplementation* _implementation = new FishObjectImplementation();
	_impl = _implementation;
	_impl->_setStub(this);
}

FishObject::FishObject(DummyConstructorParameter* param) : TangibleObject(param) {
}

FishObject::~FishObject() {
}


void FishObject::initializeTransientMembers() {
	FishObjectImplementation* _implementation = (FishObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 6);

		method.executeWithVoidReturn();
	} else
		_implementation->initializeTransientMembers();
}

void FishObject::setAttributes(String& playerName, int planetID, String& timestamp, float fishLength) {
	FishObjectImplementation* _implementation = (FishObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 7);
		method.addAsciiParameter(playerName);
		method.addSignedIntParameter(planetID);
		method.addAsciiParameter(timestamp);
		method.addFloatParameter(fishLength);

		method.executeWithVoidReturn();
	} else
		_implementation->setAttributes(playerName, planetID, timestamp, fishLength);
}

void FishObject::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	FishObjectImplementation* _implementation = (FishObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 8);
		method.addObjectParameter(menuResponse);
		method.addObjectParameter(player);

		method.executeWithVoidReturn();
	} else
		_implementation->fillObjectMenuResponse(menuResponse, player);
}

int FishObject::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	FishObjectImplementation* _implementation = (FishObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 9);
		method.addObjectParameter(player);
		method.addByteParameter(selectedID);

		return method.executeWithSignedIntReturn();
	} else
		return _implementation->handleObjectMenuSelect(player, selectedID);
}

void FishObject::fillAttributeList(AttributeListMessage* msg, PlayerCreature* object) {
	FishObjectImplementation* _implementation = (FishObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 10);
		method.addObjectParameter(msg);
		method.addObjectParameter(object);

		method.executeWithVoidReturn();
	} else
		_implementation->fillAttributeList(msg, object);
}

void FishObject::filet(PlayerCreature* player) {
	FishObjectImplementation* _implementation = (FishObjectImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 11);
		method.addObjectParameter(player);

		method.executeWithVoidReturn();
	} else
		_implementation->filet(player);
}

DistributedObjectServant* FishObject::_getImplementation() {

	_updated = true;
	return _impl;
}

void FishObject::_setImplementation(DistributedObjectServant* servant) {
	_impl = servant;
}

/*
 *	FishObjectImplementation
 */

FishObjectImplementation::FishObjectImplementation(DummyConstructorParameter* param) : TangibleObjectImplementation(param) {
	_initializeImplementation();
}


FishObjectImplementation::~FishObjectImplementation() {
}


void FishObjectImplementation::finalize() {
}

void FishObjectImplementation::_initializeImplementation() {
	_setClassHelper(FishObjectHelper::instance());

	_serializationHelperMethod();
	_serializationHelperMethod();
}

void FishObjectImplementation::_setStub(DistributedObjectStub* stub) {
	_this = (FishObject*) stub;
	TangibleObjectImplementation::_setStub(stub);
}

DistributedObjectStub* FishObjectImplementation::_getStub() {
	return _this;
}

FishObjectImplementation::operator const FishObject*() {
	return _this;
}

void FishObjectImplementation::lock(bool doLock) {
	_this->lock(doLock);
}

void FishObjectImplementation::lock(ManagedObject* obj) {
	_this->lock(obj);
}

void FishObjectImplementation::rlock(bool doLock) {
	_this->rlock(doLock);
}

void FishObjectImplementation::wlock(bool doLock) {
	_this->wlock(doLock);
}

void FishObjectImplementation::wlock(ManagedObject* obj) {
	_this->wlock(obj);
}

void FishObjectImplementation::unlock(bool doLock) {
	_this->unlock(doLock);
}

void FishObjectImplementation::runlock(bool doLock) {
	_this->runlock(doLock);
}

void FishObjectImplementation::_serializationHelperMethod() {
	TangibleObjectImplementation::_serializationHelperMethod();

	_setClassName("FishObject");

}

void FishObjectImplementation::readObject(ObjectInputStream* stream) {
	uint16 _varCount = stream->readShort();
	for (int i = 0; i < _varCount; ++i) {
		String _name;
		_name.parseFromBinaryStream(stream);

		uint16 _varSize = stream->readShort();

		int _currentOffset = stream->getOffset();

		if(FishObjectImplementation::readObjectMember(stream, _name)) {
		}

		stream->setOffset(_currentOffset + _varSize);
	}

	initializeTransientMembers();
}

bool FishObjectImplementation::readObjectMember(ObjectInputStream* stream, const String& _name) {
	if (TangibleObjectImplementation::readObjectMember(stream, _name))
		return true;

	if (_name == "player") {
		TypeInfo<String >::parseFromBinaryStream(&player, stream);
		return true;
	}

	if (_name == "planet") {
		TypeInfo<int >::parseFromBinaryStream(&planet, stream);
		return true;
	}

	if (_name == "timeCaught") {
		TypeInfo<String >::parseFromBinaryStream(&timeCaught, stream);
		return true;
	}

	if (_name == "length") {
		TypeInfo<float >::parseFromBinaryStream(&length, stream);
		return true;
	}


	return false;
}

void FishObjectImplementation::writeObject(ObjectOutputStream* stream) {
	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = FishObjectImplementation::writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);
}

int FishObjectImplementation::writeObjectMembers(ObjectOutputStream* stream) {
	String _name;
	int _offset;
	uint16 _totalSize;
	_name = "player";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<String >::toBinaryStream(&player, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);

	_name = "planet";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<int >::toBinaryStream(&planet, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);

	_name = "timeCaught";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<String >::toBinaryStream(&timeCaught, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);

	_name = "length";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<float >::toBinaryStream(&length, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);


	return 4 + TangibleObjectImplementation::writeObjectMembers(stream);
}

FishObjectImplementation::FishObjectImplementation() {
	_initializeImplementation();
	// server/zone/objects/tangible/fishing/FishObject.idl():  		Logger.setLoggingName("FishObject");
	Logger::setLoggingName("FishObject");
	// server/zone/objects/tangible/fishing/FishObject.idl():  		player = "";
	player = "";
	// server/zone/objects/tangible/fishing/FishObject.idl():  		planet = 0;
	planet = 0;
	// server/zone/objects/tangible/fishing/FishObject.idl():  		timeCaught = "";
	timeCaught = "";
	// server/zone/objects/tangible/fishing/FishObject.idl():  		length = 0.0;
	length = 0.0;
}

void FishObjectImplementation::initializeTransientMembers() {
	// server/zone/objects/tangible/fishing/FishObject.idl():  		super.initializeTransientMembers();
	TangibleObjectImplementation::initializeTransientMembers();
	// server/zone/objects/tangible/fishing/FishObject.idl():  		Logger.setLoggingName("FishObject");
	Logger::setLoggingName("FishObject");
}

void FishObjectImplementation::setAttributes(String& playerName, int planetID, String& timestamp, float fishLength) {
	// server/zone/objects/tangible/fishing/FishObject.idl():  		player = playerName;
	player = playerName;
	// server/zone/objects/tangible/fishing/FishObject.idl():  		planet = planetID;
	planet = planetID;
	// server/zone/objects/tangible/fishing/FishObject.idl():  		timeCaught = timestamp;
	timeCaught = timestamp;
	// server/zone/objects/tangible/fishing/FishObject.idl():  		length = fishLength;
	length = fishLength;
}

/*
 *	FishObjectAdapter
 */

FishObjectAdapter::FishObjectAdapter(FishObjectImplementation* obj) : TangibleObjectAdapter(obj) {
}

enum {RPC_INITIALIZETRANSIENTMEMBERS__ = 6,RPC_SETATTRIBUTES__STRING_INT_STRING_FLOAT_,RPC_FILLOBJECTMENURESPONSE__OBJECTMENURESPONSE_PLAYERCREATURE_,RPC_HANDLEOBJECTMENUSELECT__PLAYERCREATURE_BYTE_,RPC_FILLATTRIBUTELIST__ATTRIBUTELISTMESSAGE_PLAYERCREATURE_,RPC_FILET__PLAYERCREATURE_};

Packet* FishObjectAdapter::invokeMethod(uint32 methid, DistributedMethod* inv) {
	Packet* resp = new MethodReturnMessage(0);

	switch (methid) {
	case RPC_INITIALIZETRANSIENTMEMBERS__:
		initializeTransientMembers();
		break;
	case RPC_SETATTRIBUTES__STRING_INT_STRING_FLOAT_:
		setAttributes(inv->getAsciiParameter(_param0_setAttributes__String_int_String_float_), inv->getSignedIntParameter(), inv->getAsciiParameter(_param2_setAttributes__String_int_String_float_), inv->getFloatParameter());
		break;
	case RPC_FILLOBJECTMENURESPONSE__OBJECTMENURESPONSE_PLAYERCREATURE_:
		fillObjectMenuResponse((ObjectMenuResponse*) inv->getObjectParameter(), (PlayerCreature*) inv->getObjectParameter());
		break;
	case RPC_HANDLEOBJECTMENUSELECT__PLAYERCREATURE_BYTE_:
		resp->insertSignedInt(handleObjectMenuSelect((PlayerCreature*) inv->getObjectParameter(), inv->getByteParameter()));
		break;
	case RPC_FILLATTRIBUTELIST__ATTRIBUTELISTMESSAGE_PLAYERCREATURE_:
		fillAttributeList((AttributeListMessage*) inv->getObjectParameter(), (PlayerCreature*) inv->getObjectParameter());
		break;
	case RPC_FILET__PLAYERCREATURE_:
		filet((PlayerCreature*) inv->getObjectParameter());
		break;
	default:
		return NULL;
	}

	return resp;
}

void FishObjectAdapter::initializeTransientMembers() {
	((FishObjectImplementation*) impl)->initializeTransientMembers();
}

void FishObjectAdapter::setAttributes(String& playerName, int planetID, String& timestamp, float fishLength) {
	((FishObjectImplementation*) impl)->setAttributes(playerName, planetID, timestamp, fishLength);
}

void FishObjectAdapter::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	((FishObjectImplementation*) impl)->fillObjectMenuResponse(menuResponse, player);
}

int FishObjectAdapter::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	return ((FishObjectImplementation*) impl)->handleObjectMenuSelect(player, selectedID);
}

void FishObjectAdapter::fillAttributeList(AttributeListMessage* msg, PlayerCreature* object) {
	((FishObjectImplementation*) impl)->fillAttributeList(msg, object);
}

void FishObjectAdapter::filet(PlayerCreature* player) {
	((FishObjectImplementation*) impl)->filet(player);
}

/*
 *	FishObjectHelper
 */

FishObjectHelper* FishObjectHelper::staticInitializer = FishObjectHelper::instance();

FishObjectHelper::FishObjectHelper() {
	className = "FishObject";

	Core::getObjectBroker()->registerClass(className, this);
}

void FishObjectHelper::finalizeHelper() {
	FishObjectHelper::finalize();
}

DistributedObject* FishObjectHelper::instantiateObject() {
	return new FishObject(DummyConstructorParameter::instance());
}

DistributedObjectServant* FishObjectHelper::instantiateServant() {
	return new FishObjectImplementation(DummyConstructorParameter::instance());
}

DistributedObjectAdapter* FishObjectHelper::createAdapter(DistributedObjectStub* obj) {
	DistributedObjectAdapter* adapter = new FishObjectAdapter((FishObjectImplementation*) obj->_getImplementation());

	obj->_setClassName(className);
	obj->_setClassHelper(this);

	adapter->setStub(obj);

	return adapter;
}

