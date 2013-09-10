//-----------------------------------------------------------------------------
// Gura xml module
//-----------------------------------------------------------------------------
#ifndef __MODULE_XML_H__
#define __MODULE_XML_H__
#include <gura.h>
#include <expat.h>
#include "Conv_Japanese.h"

Gura_BeginModule(xml)

Gura_DeclareUserSymbol(StartElement);
Gura_DeclareUserSymbol(EndElement);
Gura_DeclareUserSymbol(CharacterData);
Gura_DeclareUserSymbol(ProcessingInstruction);
Gura_DeclareUserSymbol(Comment);
Gura_DeclareUserSymbol(StartCdataSection);
Gura_DeclareUserSymbol(EndCdataSection);
Gura_DeclareUserSymbol(Default);
Gura_DeclareUserSymbol(DefaultExpand);
Gura_DeclareUserSymbol(ExternalEntityRef);
Gura_DeclareUserSymbol(SkippedEntity);
Gura_DeclareUserSymbol(StartNamespaceDecl);
Gura_DeclareUserSymbol(EndNamespaceDecl);
Gura_DeclareUserSymbol(XmlDecl);
Gura_DeclareUserSymbol(StartDoctypeDecl);
Gura_DeclareUserSymbol(EndDoctypeDecl);
Gura_DeclareUserSymbol(ElementDecl);
Gura_DeclareUserSymbol(AttlistDecl);
Gura_DeclareUserSymbol(EntityDecl);
Gura_DeclareUserSymbol(NotationDecl);
Gura_DeclareUserSymbol(NotStandalone);

//-----------------------------------------------------------------------------
// Parser
//-----------------------------------------------------------------------------
class Parser {
private:
	XML_Parser _parser;
public:
	Parser();
	virtual ~Parser();
	void Parse(Signal sig, Stream &stream);
	inline void StopParser() { ::XML_StopParser(_parser, XML_FALSE); }
private:
	static void XMLCALL StartElementHandler(void *userData, const XML_Char *name, const XML_Char **atts);
	static void XMLCALL EndElementHandler(void *userData, const XML_Char *name);
	static void XMLCALL CharacterDataHandler(void *userData, const XML_Char *s, int len);
	static void XMLCALL ProcessingInstructionHandler(void *userData, const XML_Char *target, const XML_Char *data);
	static void XMLCALL CommentHandler(void *userData, const XML_Char *data);
	static void XMLCALL StartCdataSectionHandler(void *userData);
	static void XMLCALL EndCdataSectionHandler(void *userData);
	static void XMLCALL DefaultHandler(void *userData, const XML_Char *s, int len);
	static void XMLCALL DefaultHandlerExpand(void *userData, const XML_Char *s, int len);
	static int  XMLCALL ExternalEntityRefHandler(XML_Parser p, const XML_Char *args, const XML_Char *base, const XML_Char *systemId, const XML_Char *publicId);
	static void XMLCALL SkippedEntityHandler(void *userData, const XML_Char *entityName, int isParameterEntity);
	static int  XMLCALL UnknownEncodingHandler(void *encodingHandlerData, const XML_Char *name, XML_Encoding *info);
	static void XMLCALL StartNamespaceDeclHandler(void *userData, const XML_Char *prefix, const XML_Char *uri);
	static void XMLCALL EndNamespaceDeclHandler(void *userData, const XML_Char *prefix);
	static void XMLCALL XmlDeclHandler(void *userData, const XML_Char *version, const XML_Char *encoding, int standalone);
	static void XMLCALL StartDoctypeDeclHandler(void *userData, const XML_Char *doctypeName, const XML_Char *systemId, const XML_Char *publicId, int hasInternalSubset);
	static void XMLCALL EndDoctypeDeclHandler(void *userData);
	static void XMLCALL ElementDeclHandler(void *userData, const XML_Char *name, XML_Content *model);
	static void XMLCALL AttlistDeclHandler(void *userData, const XML_Char *elname, const XML_Char *attname, const XML_Char *attType, const XML_Char *dflt, int isRequired);
	static void XMLCALL EntityDeclHandler(void *userData, const XML_Char *entityName, int isParameterEntity, const XML_Char *value, int valueLength, const XML_Char *base, const XML_Char *systemId, const XML_Char *publicId, const XML_Char *notationName);
	static void XMLCALL NotationDeclHandler(void *userData, const XML_Char *notationName, const XML_Char *base, const XML_Char *systemId, const XML_Char *publicId);
	static int  XMLCALL NotStandaloneHandler(void *userData);
	static int Convert_shift_jis(void *data, const char *s);
	static int Convert_euc_jp(void *data, const char *s);
	virtual void OnStartElement(const XML_Char *name, const XML_Char **atts) = 0;
	virtual void OnEndElement(const XML_Char *name) = 0;
	virtual void OnCharacterData(const XML_Char *s, int len) = 0;
	virtual void OnProcessingInstruction(const XML_Char *target, const XML_Char *data) = 0;
	virtual void OnComment(const XML_Char *data) = 0;
	virtual void OnStartCdataSection() = 0;
	virtual void OnEndCdataSection() = 0;
	virtual void OnDefault(const XML_Char *s, int len) = 0;
	virtual void OnDefaultExpand(const XML_Char *s, int len) = 0;
	virtual int  OnExternalEntityRef(XML_Parser p, const XML_Char *args, const XML_Char *base, const XML_Char *systemId, const XML_Char *publicId) = 0;
	virtual void OnSkippedEntity(const XML_Char *entityName, int isParameterEntity) = 0;
	virtual void OnStartNamespaceDecl(const XML_Char *prefix, const XML_Char *uri) = 0;
	virtual void OnEndNamespaceDecl(const XML_Char *prefix) = 0;
	virtual void OnXmlDecl(const XML_Char *version, const XML_Char *encoding, int standalone) = 0;
	virtual void OnStartDoctypeDecl(const XML_Char *doctypeName, const XML_Char *systemId, const XML_Char *publicId, int hasInternalSubset) = 0;
	virtual void OnEndDoctypeDecl() = 0;
	virtual void OnElementDecl(const XML_Char *name, XML_Content *model) = 0;
	virtual void OnAttlistDecl(const XML_Char *elname, const XML_Char *attname, const XML_Char *attType, const XML_Char *dflt, int isRequired) = 0;
	virtual void OnEntityDecl(const XML_Char *entityName, int isParameterEntity, const XML_Char *value, int valueLength, const XML_Char *base, const XML_Char *systemId, const XML_Char *publicId, const XML_Char *notationName) = 0;
	virtual void OnNotationDecl(const XML_Char *notationName, const XML_Char *base, const XML_Char *systemId, const XML_Char *publicId) = 0;
	virtual int  OnNotStandalone() = 0;
};

class ElementOwner;

//-----------------------------------------------------------------------------
// Element
//-----------------------------------------------------------------------------
class Element {
public:
	class Attribute {
	private:
		String _name;
		String _value;
	public:
		Attribute(const String &name, const String &value);
		inline const char *GetName() const { return _name.c_str(); }
		inline const char *GetValue() const { return _value.c_str(); }
	};
	class AttributeList : public std::vector<Attribute *> {
	public:
		Attribute *FindByName(const char *name);
	};
	class AttributeOwner : public AttributeList {
	public:
		~AttributeOwner();
		void Clear();
	};
private:
	int _cntRef;
	String _name;
	AttributeOwner _attributes;
	std::auto_ptr<ElementOwner> _pChildren;
public:
	Gura_DeclareReferenceAccessor(Element);
public:
	Element();
	void SetAttributes(const char **atts);
	inline const char *GetName() const { return _name.c_str(); }
	inline AttributeOwner &GetAttributes() { return _attributes; }
	inline const AttributeOwner &GetAttributes() const { return _attributes; }
	inline ElementOwner &GetChildren() { return *_pChildren; }
	inline const ElementOwner &GetChildren() const { return *_pChildren; }
private:
	inline ~Element() {}
};

//-----------------------------------------------------------------------------
// ElementList
//-----------------------------------------------------------------------------
class ElementList : public std::vector<Element *> {
};

//-----------------------------------------------------------------------------
// ElementOwner
//-----------------------------------------------------------------------------
class ElementOwner : public ElementList {
public:
	~ElementOwner();
	void Clear();
};

//-----------------------------------------------------------------------------
// Object_element
//-----------------------------------------------------------------------------
Gura_DeclareUserClass(element);

class Object_element : public Object_dict {
private:
	ValueList *_pValList;
	//AutoPtr<Element> _pElement;
public:
	Gura_DeclareObjectAccessor(element)
public:
	Object_element(Environment &env, const char *name, const char **atts);
	//inline Element *GetElement() { return _pElement.get(); }
	//inline const Element *GetElement() const { return _pElement.get(); }
	void AddChild(const Value &value);
	String Format(Signal sig, int indentLevel) const;
	String GetText(Signal sig) const;
	virtual String ToString(Signal sig, bool exprFlag);
};

//-----------------------------------------------------------------------------
// Object_parser
//-----------------------------------------------------------------------------
class Object_parser : public Object {
public:
	class ParserEx : public Parser {
	private:
		Object_parser *_pObj;
	public:
		inline ParserEx(Object_parser *pObj) : _pObj(pObj) {}
	private:
		virtual void OnStartElement(const XML_Char *name, const XML_Char **atts);
		virtual void OnEndElement(const XML_Char *name);
		virtual void OnCharacterData(const XML_Char *s, int len);
		virtual void OnProcessingInstruction(const XML_Char *target, const XML_Char *data);
		virtual void OnComment(const XML_Char *data);
		virtual void OnStartCdataSection();
		virtual void OnEndCdataSection();
		virtual void OnDefault(const XML_Char *s, int len);
		virtual void OnDefaultExpand(const XML_Char *s, int len);
		virtual int  OnExternalEntityRef(XML_Parser p, const XML_Char *args, const XML_Char *base, const XML_Char *systemId, const XML_Char *publicId);
		virtual void OnSkippedEntity(const XML_Char *entityName, int isParameterEntity);
		virtual void OnStartNamespaceDecl(const XML_Char *prefix, const XML_Char *uri);
		virtual void OnEndNamespaceDecl(const XML_Char *prefix);
		virtual void OnXmlDecl(const XML_Char *version, const XML_Char *encoding, int standalone);
		virtual void OnStartDoctypeDecl(const XML_Char *doctypeName, const XML_Char *systemId, const XML_Char *publicId, int hasInternalSubset);
		virtual void OnEndDoctypeDecl();
		virtual void OnElementDecl(const XML_Char *name, XML_Content *model);
		virtual void OnAttlistDecl(const XML_Char *elname, const XML_Char *attname, const XML_Char *attType, const XML_Char *dflt, int isRequired);
		virtual void OnEntityDecl(const XML_Char *entityName, int isParameterEntity, const XML_Char *value, int valueLength, const XML_Char *base, const XML_Char *systemId, const XML_Char *publicId, const XML_Char *notationName);
		virtual void OnNotationDecl(const XML_Char *notationName, const XML_Char *base, const XML_Char *systemId, const XML_Char *publicId);
		virtual int  OnNotStandalone();
	};
private:
	ParserEx _parser;
	Signal *_pSig;
public:
	Gura_DeclareObjectAccessor(parser)
public:
	Object_parser(Class *pClass);
	virtual ~Object_parser();
	void Parse(Environment &env, Signal &sig, Stream &stream);
	void CallHandler(const Symbol *pSymbol, const ValueList argList);
};

//-----------------------------------------------------------------------------
// Reader
//-----------------------------------------------------------------------------
class Reader : public Parser {
private:
	typedef std::vector<Object_element *> Stack;
private:
	Stack _stack;
	Object_element *_pObjElemRoot;
	Environment *_pEnv;
	Signal *_pSig;
public:
	inline Reader() : _pEnv(NULL), _pSig(NULL), _pObjElemRoot(NULL) {}
	Object_element *Parse(Environment &env, Signal &sig, Stream &stream);
private:
	virtual void OnStartElement(const XML_Char *name, const XML_Char **atts);
	virtual void OnEndElement(const XML_Char *name);
	virtual void OnCharacterData(const XML_Char *s, int len);
	virtual void OnProcessingInstruction(const XML_Char *target, const XML_Char *data);
	virtual void OnComment(const XML_Char *data);
	virtual void OnStartCdataSection();
	virtual void OnEndCdataSection();
	virtual void OnDefault(const XML_Char *s, int len);
	virtual void OnDefaultExpand(const XML_Char *s, int len);
	virtual int  OnExternalEntityRef(XML_Parser p, const XML_Char *args, const XML_Char *base, const XML_Char *systemId, const XML_Char *publicId);
	virtual void OnSkippedEntity(const XML_Char *entityName, int isParameterEntity);
	virtual void OnStartNamespaceDecl(const XML_Char *prefix, const XML_Char *uri);
	virtual void OnEndNamespaceDecl(const XML_Char *prefix);
	virtual void OnXmlDecl(const XML_Char *version, const XML_Char *encoding, int standalone);
	virtual void OnStartDoctypeDecl(const XML_Char *doctypeName, const XML_Char *systemId, const XML_Char *publicId, int hasInternalSubset);
	virtual void OnEndDoctypeDecl();
	virtual void OnElementDecl(const XML_Char *name, XML_Content *model);
	virtual void OnAttlistDecl(const XML_Char *elname, const XML_Char *attname, const XML_Char *attType, const XML_Char *dflt, int isRequired);
	virtual void OnEntityDecl(const XML_Char *entityName, int isParameterEntity, const XML_Char *value, int valueLength, const XML_Char *base, const XML_Char *systemId, const XML_Char *publicId, const XML_Char *notationName);
	virtual void OnNotationDecl(const XML_Char *notationName, const XML_Char *base, const XML_Char *systemId, const XML_Char *publicId);
	virtual int  OnNotStandalone();
};

}}

#endif
