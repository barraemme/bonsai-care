/****************************************************************************
** Meta object code from reading C++ file 'bonsaimodel.h'
**
** Created: Tue 31. Jan 19:05:33 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../bonsaimodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bonsaimodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BonsaiModel[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,   21,   12,   12, 0x0a,

 // methods: signature, parameters, type, tag, flags
      46,   12,   42,   12, 0x02,
      68,   63,   55,   12, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_BonsaiModel[] = {
    "BonsaiModel\0\0fetch()\0item\0addRow(Bonsai*)\0"
    "int\0nextId()\0QString\0date\0getAgeString(QDate)\0"
};

const QMetaObject BonsaiModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_BonsaiModel,
      qt_meta_data_BonsaiModel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BonsaiModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BonsaiModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BonsaiModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BonsaiModel))
        return static_cast<void*>(const_cast< BonsaiModel*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int BonsaiModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: fetch(); break;
        case 1: addRow((*reinterpret_cast< Bonsai*(*)>(_a[1]))); break;
        case 2: { int _r = nextId();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { QString _r = getAgeString((*reinterpret_cast< QDate(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void BonsaiModel::fetch()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
