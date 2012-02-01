/****************************************************************************
** Meta object code from reading C++ file 'operation.h'
**
** Created: Tue 31. Jan 19:05:40 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../operation.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'operation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Operation[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   10,   11,   10, 0x0a,
      23,   10,   10,   10, 0x0a,
      37,   10,   11,   10, 0x0a,
      48,   10,   10,   10, 0x0a,
      71,   10,   65,   10, 0x0a,
      87,   82,   10,   10, 0x0a,
     114,   10,  106,   10, 0x0a,
     126,  121,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Operation[] = {
    "Operation\0\0int\0index()\0setIndex(int)\0"
    "bonsaiId()\0setBonsaiId(int)\0QDate\0"
    "lastDate()\0date\0setLastDate(QDate)\0"
    "QString\0name()\0name\0setName(QString)\0"
};

const QMetaObject Operation::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Operation,
      qt_meta_data_Operation, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Operation::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Operation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Operation::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Operation))
        return static_cast<void*>(const_cast< Operation*>(this));
    return QObject::qt_metacast(_clname);
}

int Operation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { int _r = index();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: setIndex((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: { int _r = bonsaiId();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: setBonsaiId((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: { QDate _r = lastDate();
            if (_a[0]) *reinterpret_cast< QDate*>(_a[0]) = _r; }  break;
        case 5: setLastDate((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 6: { QString _r = name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 7: setName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
