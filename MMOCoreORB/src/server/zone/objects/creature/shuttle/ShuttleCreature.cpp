/*
 *	server/zone/objects/creature/shuttle/ShuttleCreature.cpp generated by engine3 IDL compiler 0.60
 */

#include "ShuttleCreature.h"

#include "server/zone/Zone.h"

#include "server/zone/objects/player/PlayerCreature.h"

#include "server/zone/objects/tangible/ticket/TicketObject.h"

#include "server/zone/managers/planet/PlanetManager.h"

#include "server/zone/Zone.h"

#include "server/zone/ZoneServer.h"

#include "server/zone/objects/creature/shuttle/ShuttleLandingEvent.h"

#include "server/zone/objects/creature/shuttle/ShuttleTakeOffEvent.h"

/*
 *	ShuttleCreatureStub
 */

ShuttleCreature::ShuttleCreature() : CreatureObject(DummyConstructorParameter::instance()) {
	ShuttleCreatureImplementation* _implementation = new ShuttleCreatureImplementation();
	_impl = _implementation;
	_impl->_setStub(this);
}

ShuttleCreature::ShuttleCreature(DummyConstructorParameter* param) : CreatureObject(param) {
}

ShuttleCreature::~ShuttleCreature() {
}


void ShuttleCreature::doTakeOff() {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 6);

		method.executeWithVoidReturn();
	} else
		_implementation->doTakeOff();
}

void ShuttleCreature::doLanding() {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 7);

		method.executeWithVoidReturn();
	} else
		_implementation->doLanding();
}

void ShuttleCreature::activateRecovery() {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 8);

		method.executeWithVoidReturn();
	} else
		_implementation->activateRecovery();
}

bool ShuttleCreature::isAttackableBy(CreatureObject* object) {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 9);
		method.addObjectParameter(object);

		return method.executeWithBooleanReturn();
	} else
		return _implementation->isAttackableBy(object);
}

void ShuttleCreature::sendPlayerTo(PlayerCreature* player, TicketObject* ticket) {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 10);
		method.addObjectParameter(player);
		method.addObjectParameter(ticket);

		method.executeWithVoidReturn();
	} else
		_implementation->sendPlayerTo(player, ticket);
}

int ShuttleCreature::getArrivalTime() {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 11);

		return method.executeWithSignedIntReturn();
	} else
		return _implementation->getArrivalTime();
}

long long ShuttleCreature::getLandingTime() {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 12);

		return method.executeWithSignedLongReturn();
	} else
		return _implementation->getLandingTime();
}

void ShuttleCreature::getArrivalPoint(float& x, float& y, float& z) {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		throw ObjectNotLocalException(this);

	} else
		_implementation->getArrivalPoint(x, y, z);
}

void ShuttleCreature::setArrivalPoint(float x, float y, float z) {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 13);
		method.addFloatParameter(x);
		method.addFloatParameter(y);
		method.addFloatParameter(z);

		method.executeWithVoidReturn();
	} else
		_implementation->setArrivalPoint(x, y, z);
}

void ShuttleCreature::setStarport(bool st) {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 14);
		method.addBooleanParameter(st);

		method.executeWithVoidReturn();
	} else
		_implementation->setStarport(st);
}

void ShuttleCreature::setPlanet(const String& plan) {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 15);
		method.addAsciiParameter(plan);

		method.executeWithVoidReturn();
	} else
		_implementation->setPlanet(plan);
}

void ShuttleCreature::setCity(const String& cit) {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 16);
		method.addAsciiParameter(cit);

		method.executeWithVoidReturn();
	} else
		_implementation->setCity(cit);
}

void ShuttleCreature::setTax(unsigned int t) {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 17);
		method.addUnsignedIntParameter(t);

		method.executeWithVoidReturn();
	} else
		_implementation->setTax(t);
}

String ShuttleCreature::getPlanet() {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 18);

		method.executeWithAsciiReturn(_return_getPlanet);
		return _return_getPlanet;
	} else
		return _implementation->getPlanet();
}

String ShuttleCreature::getCity() {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 19);

		method.executeWithAsciiReturn(_return_getCity);
		return _return_getCity;
	} else
		return _implementation->getCity();
}

unsigned int ShuttleCreature::getTax() {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 20);

		return method.executeWithUnsignedIntReturn();
	} else
		return _implementation->getTax();
}

bool ShuttleCreature::isStarport() {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 21);

		return method.executeWithBooleanReturn();
	} else
		return _implementation->isStarport();
}

bool ShuttleCreature::isShuttleCreature() {
	ShuttleCreatureImplementation* _implementation = (ShuttleCreatureImplementation*) _getImplementation();
	if (_implementation == NULL) {
		if (!deployed)
			throw ObjectNotDeployedException(this);

		DistributedMethod method(this, 22);

		return method.executeWithBooleanReturn();
	} else
		return _implementation->isShuttleCreature();
}

DistributedObjectServant* ShuttleCreature::_getImplementation() {

	_updated = true;
	return _impl;
}

void ShuttleCreature::_setImplementation(DistributedObjectServant* servant) {
	_impl = servant;
}

/*
 *	ShuttleCreatureImplementation
 */

ShuttleCreatureImplementation::ShuttleCreatureImplementation(DummyConstructorParameter* param) : CreatureObjectImplementation(param) {
	_initializeImplementation();
}


ShuttleCreatureImplementation::~ShuttleCreatureImplementation() {
}


void ShuttleCreatureImplementation::finalize() {
}

void ShuttleCreatureImplementation::_initializeImplementation() {
	_setClassHelper(ShuttleCreatureHelper::instance());

	_serializationHelperMethod();
	_serializationHelperMethod();
}

void ShuttleCreatureImplementation::_setStub(DistributedObjectStub* stub) {
	_this = (ShuttleCreature*) stub;
	CreatureObjectImplementation::_setStub(stub);
}

DistributedObjectStub* ShuttleCreatureImplementation::_getStub() {
	return _this;
}

ShuttleCreatureImplementation::operator const ShuttleCreature*() {
	return _this;
}

void ShuttleCreatureImplementation::lock(bool doLock) {
	_this->lock(doLock);
}

void ShuttleCreatureImplementation::lock(ManagedObject* obj) {
	_this->lock(obj);
}

void ShuttleCreatureImplementation::rlock(bool doLock) {
	_this->rlock(doLock);
}

void ShuttleCreatureImplementation::wlock(bool doLock) {
	_this->wlock(doLock);
}

void ShuttleCreatureImplementation::wlock(ManagedObject* obj) {
	_this->wlock(obj);
}

void ShuttleCreatureImplementation::unlock(bool doLock) {
	_this->unlock(doLock);
}

void ShuttleCreatureImplementation::runlock(bool doLock) {
	_this->runlock(doLock);
}

void ShuttleCreatureImplementation::_serializationHelperMethod() {
	CreatureObjectImplementation::_serializationHelperMethod();

	_setClassName("ShuttleCreature");

}

void ShuttleCreatureImplementation::readObject(ObjectInputStream* stream) {
	uint16 _varCount = stream->readShort();
	for (int i = 0; i < _varCount; ++i) {
		String _name;
		_name.parseFromBinaryStream(stream);

		uint16 _varSize = stream->readShort();

		int _currentOffset = stream->getOffset();

		if(ShuttleCreatureImplementation::readObjectMember(stream, _name)) {
		}

		stream->setOffset(_currentOffset + _varSize);
	}

	initializeTransientMembers();
}

bool ShuttleCreatureImplementation::readObjectMember(ObjectInputStream* stream, const String& _name) {
	if (CreatureObjectImplementation::readObjectMember(stream, _name))
		return true;

	if (_name == "planet") {
		TypeInfo<String >::parseFromBinaryStream(&planet, stream);
		return true;
	}

	if (_name == "city") {
		TypeInfo<String >::parseFromBinaryStream(&city, stream);
		return true;
	}

	if (_name == "tax") {
		TypeInfo<unsigned int >::parseFromBinaryStream(&tax, stream);
		return true;
	}

	if (_name == "starport") {
		TypeInfo<bool >::parseFromBinaryStream(&starport, stream);
		return true;
	}

	if (_name == "arrivalPositionX") {
		TypeInfo<float >::parseFromBinaryStream(&arrivalPositionX, stream);
		return true;
	}

	if (_name == "arrivalPositionZ") {
		TypeInfo<float >::parseFromBinaryStream(&arrivalPositionZ, stream);
		return true;
	}

	if (_name == "arrivalPositionY") {
		TypeInfo<float >::parseFromBinaryStream(&arrivalPositionY, stream);
		return true;
	}


	return false;
}

void ShuttleCreatureImplementation::writeObject(ObjectOutputStream* stream) {
	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = ShuttleCreatureImplementation::writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);
}

int ShuttleCreatureImplementation::writeObjectMembers(ObjectOutputStream* stream) {
	String _name;
	int _offset;
	uint16 _totalSize;
	_name = "planet";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<String >::toBinaryStream(&planet, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);

	_name = "city";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<String >::toBinaryStream(&city, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);

	_name = "tax";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<unsigned int >::toBinaryStream(&tax, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);

	_name = "starport";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<bool >::toBinaryStream(&starport, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);

	_name = "arrivalPositionX";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<float >::toBinaryStream(&arrivalPositionX, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);

	_name = "arrivalPositionZ";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<float >::toBinaryStream(&arrivalPositionZ, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);

	_name = "arrivalPositionY";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeShort(0);
	TypeInfo<float >::toBinaryStream(&arrivalPositionY, stream);
	_totalSize = (uint16) (stream->getOffset() - (_offset + 2));
	stream->writeShort(_offset, _totalSize);


	return 7 + CreatureObjectImplementation::writeObjectMembers(stream);
}

ShuttleCreatureImplementation::ShuttleCreatureImplementation() {
	_initializeImplementation();
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		Logger.setLoggingName("ShuttleCreature");
	Logger::setLoggingName("ShuttleCreature");
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		Logger.setLogging(false);
	Logger::setLogging(false);
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		Logger.setGlobalLogging(true);
	Logger::setGlobalLogging(true);
}

void ShuttleCreatureImplementation::activateRecovery() {
}

bool ShuttleCreatureImplementation::isAttackableBy(CreatureObject* object) {
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		return false;
	return false;
}

int ShuttleCreatureImplementation::getArrivalTime() {
	Locker _locker(_this);
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		PlanetManager 
	if (CreatureObjectImplementation::zone.getForUpdate() == NULL)	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  			return 0;
	return 0;
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		PlanetManager planetManager = super.zone.getPlanetManager();
	PlanetManager* planetManager = CreatureObjectImplementation::zone.getForUpdate()->getPlanetManager();
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		long land = getLandingTime();
	long long land = getLandingTime();
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		int t = (land / 1000) * -1;
	int t = (land / 1000) * -1;
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		return t;
	return t;
}

void ShuttleCreatureImplementation::getArrivalPoint(float& x, float& y, float& z) {
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		x = arrivalPositionX;
	x = arrivalPositionX;
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		y = arrivalPositionY;
	y = arrivalPositionY;
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		z = arrivalPositionZ;
	z = arrivalPositionZ;
}

void ShuttleCreatureImplementation::setArrivalPoint(float x, float y, float z) {
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		arrivalPositionX = x;
	arrivalPositionX = x;
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		arrivalPositionY = y;
	arrivalPositionY = y;
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		arrivalPositionZ = z;
	arrivalPositionZ = z;
}

void ShuttleCreatureImplementation::setStarport(bool st) {
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		starport = st;
	starport = st;
}

void ShuttleCreatureImplementation::setPlanet(const String& plan) {
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		planet = plan;
	planet = plan;
}

void ShuttleCreatureImplementation::setCity(const String& cit) {
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		city = cit;
	city = cit;
}

void ShuttleCreatureImplementation::setTax(unsigned int t) {
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		tax = t;
	tax = t;
}

String ShuttleCreatureImplementation::getPlanet() {
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		return planet;
	return planet;
}

String ShuttleCreatureImplementation::getCity() {
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		return city;
	return city;
}

unsigned int ShuttleCreatureImplementation::getTax() {
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		return tax;
	return tax;
}

bool ShuttleCreatureImplementation::isStarport() {
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		return starport;
	return starport;
}

bool ShuttleCreatureImplementation::isShuttleCreature() {
	// server/zone/objects/creature/shuttle/ShuttleCreature.idl():  		return true;
	return true;
}

/*
 *	ShuttleCreatureAdapter
 */

ShuttleCreatureAdapter::ShuttleCreatureAdapter(ShuttleCreatureImplementation* obj) : CreatureObjectAdapter(obj) {
}

enum {RPC_DOTAKEOFF__ = 6,RPC_DOLANDING__,RPC_ACTIVATERECOVERY__,RPC_ISATTACKABLEBY__CREATUREOBJECT_,RPC_SENDPLAYERTO__PLAYERCREATURE_TICKETOBJECT_,RPC_GETARRIVALTIME__,RPC_GETLANDINGTIME__,RPC_SETARRIVALPOINT__FLOAT_FLOAT_FLOAT_,RPC_SETSTARPORT__BOOL_,RPC_SETPLANET__STRING_,RPC_SETCITY__STRING_,RPC_SETTAX__INT_,RPC_GETPLANET__,RPC_GETCITY__,RPC_GETTAX__,RPC_ISSTARPORT__,RPC_ISSHUTTLECREATURE__};

Packet* ShuttleCreatureAdapter::invokeMethod(uint32 methid, DistributedMethod* inv) {
	Packet* resp = new MethodReturnMessage(0);

	switch (methid) {
	case RPC_DOTAKEOFF__:
		doTakeOff();
		break;
	case RPC_DOLANDING__:
		doLanding();
		break;
	case RPC_ACTIVATERECOVERY__:
		activateRecovery();
		break;
	case RPC_ISATTACKABLEBY__CREATUREOBJECT_:
		resp->insertBoolean(isAttackableBy((CreatureObject*) inv->getObjectParameter()));
		break;
	case RPC_SENDPLAYERTO__PLAYERCREATURE_TICKETOBJECT_:
		sendPlayerTo((PlayerCreature*) inv->getObjectParameter(), (TicketObject*) inv->getObjectParameter());
		break;
	case RPC_GETARRIVALTIME__:
		resp->insertSignedInt(getArrivalTime());
		break;
	case RPC_GETLANDINGTIME__:
		resp->insertSignedLong(getLandingTime());
		break;
	case RPC_SETARRIVALPOINT__FLOAT_FLOAT_FLOAT_:
		setArrivalPoint(inv->getFloatParameter(), inv->getFloatParameter(), inv->getFloatParameter());
		break;
	case RPC_SETSTARPORT__BOOL_:
		setStarport(inv->getBooleanParameter());
		break;
	case RPC_SETPLANET__STRING_:
		setPlanet(inv->getAsciiParameter(_param0_setPlanet__String_));
		break;
	case RPC_SETCITY__STRING_:
		setCity(inv->getAsciiParameter(_param0_setCity__String_));
		break;
	case RPC_SETTAX__INT_:
		setTax(inv->getUnsignedIntParameter());
		break;
	case RPC_GETPLANET__:
		resp->insertAscii(getPlanet());
		break;
	case RPC_GETCITY__:
		resp->insertAscii(getCity());
		break;
	case RPC_GETTAX__:
		resp->insertInt(getTax());
		break;
	case RPC_ISSTARPORT__:
		resp->insertBoolean(isStarport());
		break;
	case RPC_ISSHUTTLECREATURE__:
		resp->insertBoolean(isShuttleCreature());
		break;
	default:
		return NULL;
	}

	return resp;
}

void ShuttleCreatureAdapter::doTakeOff() {
	((ShuttleCreatureImplementation*) impl)->doTakeOff();
}

void ShuttleCreatureAdapter::doLanding() {
	((ShuttleCreatureImplementation*) impl)->doLanding();
}

void ShuttleCreatureAdapter::activateRecovery() {
	((ShuttleCreatureImplementation*) impl)->activateRecovery();
}

bool ShuttleCreatureAdapter::isAttackableBy(CreatureObject* object) {
	return ((ShuttleCreatureImplementation*) impl)->isAttackableBy(object);
}

void ShuttleCreatureAdapter::sendPlayerTo(PlayerCreature* player, TicketObject* ticket) {
	((ShuttleCreatureImplementation*) impl)->sendPlayerTo(player, ticket);
}

int ShuttleCreatureAdapter::getArrivalTime() {
	return ((ShuttleCreatureImplementation*) impl)->getArrivalTime();
}

long long ShuttleCreatureAdapter::getLandingTime() {
	return ((ShuttleCreatureImplementation*) impl)->getLandingTime();
}

void ShuttleCreatureAdapter::setArrivalPoint(float x, float y, float z) {
	((ShuttleCreatureImplementation*) impl)->setArrivalPoint(x, y, z);
}

void ShuttleCreatureAdapter::setStarport(bool st) {
	((ShuttleCreatureImplementation*) impl)->setStarport(st);
}

void ShuttleCreatureAdapter::setPlanet(const String& plan) {
	((ShuttleCreatureImplementation*) impl)->setPlanet(plan);
}

void ShuttleCreatureAdapter::setCity(const String& cit) {
	((ShuttleCreatureImplementation*) impl)->setCity(cit);
}

void ShuttleCreatureAdapter::setTax(unsigned int t) {
	((ShuttleCreatureImplementation*) impl)->setTax(t);
}

String ShuttleCreatureAdapter::getPlanet() {
	return ((ShuttleCreatureImplementation*) impl)->getPlanet();
}

String ShuttleCreatureAdapter::getCity() {
	return ((ShuttleCreatureImplementation*) impl)->getCity();
}

unsigned int ShuttleCreatureAdapter::getTax() {
	return ((ShuttleCreatureImplementation*) impl)->getTax();
}

bool ShuttleCreatureAdapter::isStarport() {
	return ((ShuttleCreatureImplementation*) impl)->isStarport();
}

bool ShuttleCreatureAdapter::isShuttleCreature() {
	return ((ShuttleCreatureImplementation*) impl)->isShuttleCreature();
}

/*
 *	ShuttleCreatureHelper
 */

ShuttleCreatureHelper* ShuttleCreatureHelper::staticInitializer = ShuttleCreatureHelper::instance();

ShuttleCreatureHelper::ShuttleCreatureHelper() {
	className = "ShuttleCreature";

	Core::getObjectBroker()->registerClass(className, this);
}

void ShuttleCreatureHelper::finalizeHelper() {
	ShuttleCreatureHelper::finalize();
}

DistributedObject* ShuttleCreatureHelper::instantiateObject() {
	return new ShuttleCreature(DummyConstructorParameter::instance());
}

DistributedObjectServant* ShuttleCreatureHelper::instantiateServant() {
	return new ShuttleCreatureImplementation(DummyConstructorParameter::instance());
}

DistributedObjectAdapter* ShuttleCreatureHelper::createAdapter(DistributedObjectStub* obj) {
	DistributedObjectAdapter* adapter = new ShuttleCreatureAdapter((ShuttleCreatureImplementation*) obj->_getImplementation());

	obj->_setClassName(className);
	obj->_setClassHelper(this);

	adapter->setStub(obj);

	return adapter;
}

