/****************************************************************************
** Meta object code from reading C++ file 'useractiondlg.h'
**
** Created: Tue Apr 14 09:44:30 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../useractiondlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'useractiondlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UserActionDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      30,   15,   14,   14, 0x05,
      63,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     109,  103,   14,   14, 0x0a,
     143,   14,   14,   14, 0x08,
     179,  167,   14,   14, 0x08,
     232,  227,   14,   14, 0x08,
     281,  227,   14,   14, 0x08,
     330,  227,   14,   14, 0x08,
     378,  227,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_UserActionDlg[] = {
    "UserActionDlg\0\0targetId,table\0"
    "emitCallInfo(uint,QTableWidget*)\0"
    "emitKeyboardInfo(uint,PageTableWidget*)\0"
    "tarId\0onQueryKeyboardInfoFinished(uint)\0"
    "RefreshUserActionData()\0item,column\0"
    "onTrUserActionItemClicked(QTreeWidgetItem*,int)\0"
    "item\0onTbKeyboardRecordItemClicked(QTableWidgetItem*)\0"
    "onTbPasswordRecordItemClicked(QTableWidgetItem*)\0"
    "onTbClipboardDataItemClicked(QTableWidgetItem*)\0"
    "onTbMessageInfoItemClicked(QTableWidgetItem*)\0"
};

void UserActionDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UserActionDlg *_t = static_cast<UserActionDlg *>(_o);
        switch (_id) {
        case 0: _t->emitCallInfo((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QTableWidget*(*)>(_a[2]))); break;
        case 1: _t->emitKeyboardInfo((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< PageTableWidget*(*)>(_a[2]))); break;
        case 2: _t->onQueryKeyboardInfoFinished((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 3: _t->RefreshUserActionData(); break;
        case 4: _t->onTrUserActionItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->onTbKeyboardRecordItemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 6: _t->onTbPasswordRecordItemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->onTbClipboardDataItemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 8: _t->onTbMessageInfoItemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UserActionDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UserActionDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UserActionDlg,
      qt_meta_data_UserActionDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UserActionDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UserActionDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UserActionDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UserActionDlg))
        return static_cast<void*>(const_cast< UserActionDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int UserActionDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void UserActionDlg::emitCallInfo(unsigned int _t1, QTableWidget * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UserActionDlg::emitKeyboardInfo(unsigned int _t1, PageTableWidget * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
