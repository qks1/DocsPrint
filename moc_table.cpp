/****************************************************************************
** Meta object code from reading C++ file 'table.h'
**
** Created: Wed Jul 25 16:22:12 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "table.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'table.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MTable[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      28,    7,    7,    7, 0x08,
      44,    7,    7,    7, 0x08,
      67,    7,    7,    7, 0x08,
      77,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MTable[] = {
    "MTable\0\0date_changed(QDate)\0switch_hidden()\0"
    "checkbox_used(QString)\0refresh()\0"
    "double_click(QModelIndex)\0"
};

void MTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MTable *_t = static_cast<MTable *>(_o);
        switch (_id) {
        case 0: _t->date_changed((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 1: _t->switch_hidden(); break;
        case 2: _t->checkbox_used((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->refresh(); break;
        case 4: _t->double_click((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MTable::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MTable,
      qt_meta_data_MTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MTable))
        return static_cast<void*>(const_cast< MTable*>(this));
    return QWidget::qt_metacast(_clname);
}

int MTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
