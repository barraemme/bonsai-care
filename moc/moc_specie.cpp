/****************************************************************************
** Meta object code from reading C++ file 'specie.h'
**
** Created: Fri 10. Feb 18:31:19 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../specie.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'specie.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Specie[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,    7,    8,    7, 0x0a,
      29,    7,   25,    7, 0x0a,
      37,    7,    7,    7, 0x0a,
      59,    7,   51,    7, 0x0a,
      71,   66,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Specie[] = {
    "Specie\0\0QObject*\0items()\0int\0index()\0"
    "setIndex(int)\0QString\0name()\0name\0"
    "setName(QString)\0"
};

const QMetaObject Specie::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Specie,
      qt_meta_data_Specie, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Specie::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Specie::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Specie::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Specie))
        return static_cast<void*>(const_cast< Specie*>(this));
    return QObject::qt_metacast(_clname);
}

int Specie::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { QObject* _r = items();
            if (_a[0]) *reinterpret_cast< QObject**>(_a[0]) = _r; }  break;
        case 1: { int _r = index();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: setIndex((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: { QString _r = name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: setName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
