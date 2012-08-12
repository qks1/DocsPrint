/****************************************************************************
** Meta object code from reading C++ file 'mtable.h'
**
** Created: Thu 2. Aug 09:37:30 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mtable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mtable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MTable[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,    8,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      66,    7,    7,    7, 0x08,
      86,    7,    7,    7, 0x08,
     102,    7,    7,    7, 0x08,
     125,    7,    7,    7, 0x08,
     135,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MTable[] = {
    "MTable\0\0,,,,\0"
    "show_doc_signal(int,QString,QString,QString,QString)\0"
    "date_changed(QDate)\0switch_hidden()\0"
    "checkbox_used(QString)\0refresh()\0"
    "double_click(QModelIndex)\0"
};

void MTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MTable *_t = static_cast<MTable *>(_o);
        switch (_id) {
        case 0: _t->show_doc_signal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 1: _t->date_changed((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 2: _t->switch_hidden(); break;
        case 3: _t->checkbox_used((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->refresh(); break;
        case 5: _t->double_click((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
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
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void MTable::show_doc_signal(int _t1, QString _t2, QString _t3, QString _t4, QString _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
