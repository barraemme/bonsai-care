/****************************************************************************
** Meta object code from reading C++ file 'bonsaiitem.h'
**
** Created: Tue 31. Jan 19:05:35 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../bonsaiitem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bonsaiitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BonsaiItem[] = {

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
      21,   11,   12,   11, 0x0a,
      33,   11,   29,   11, 0x0a,
      41,   11,   11,   11, 0x0a,
      63,   11,   55,   11, 0x0a,
      75,   70,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BonsaiItem[] = {
    "BonsaiItem\0\0QObject*\0items()\0int\0"
    "index()\0setIndex(int)\0QString\0name()\0"
    "name\0setName(QString)\0"
};

const QMetaObject BonsaiItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BonsaiItem,
      qt_meta_data_BonsaiItem, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BonsaiItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BonsaiItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BonsaiItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BonsaiItem))
        return static_cast<void*>(const_cast< BonsaiItem*>(this));
    return QObject::qt_metacast(_clname);
}

int BonsaiItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
