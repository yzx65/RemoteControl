/****************************************************************************
** Meta object code from reading C++ file 'multimediadlg.h'
**
** Created: Tue Mar 31 10:16:07 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../multimediadlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'multimediadlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MultimediaDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x08,
      65,   15,   14,   14, 0x08,
     108,   15,   14,   14, 0x08,
     151,   15,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MultimediaDlg[] = {
    "MultimediaDlg\0\0item\0"
    "onLstMonitorAppItemClicked(QListWidgetItem*)\0"
    "onLstSaveTimeItemClicked(QListWidgetItem*)\0"
    "onLstFileTypeItemClicked(QListWidgetItem*)\0"
    "onLstFileListItemDoubleClicked(QListWidgetItem*)\0"
};

void MultimediaDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MultimediaDlg *_t = static_cast<MultimediaDlg *>(_o);
        switch (_id) {
        case 0: _t->onLstMonitorAppItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->onLstSaveTimeItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->onLstFileTypeItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->onLstFileListItemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MultimediaDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MultimediaDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MultimediaDlg,
      qt_meta_data_MultimediaDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MultimediaDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MultimediaDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MultimediaDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MultimediaDlg))
        return static_cast<void*>(const_cast< MultimediaDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int MultimediaDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
