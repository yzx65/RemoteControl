/****************************************************************************
** Meta object code from reading C++ file 'remotecmddlg.h'
**
** Created: Thu Sep 10 21:18:22 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../remotecmddlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'remotecmddlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RemoteCmdDlg[] = {

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
      14,   13,   13,   13, 0x08,
      36,   13,   13,   13, 0x08,
      68,   13,   13,   13, 0x08,
     101,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RemoteCmdDlg[] = {
    "RemoteCmdDlg\0\0onBtnWinExecClicked()\0"
    "onBtnExecuteConsoleCmdClicked()\0"
    "onBtnClearConsoleOutputClicked()\0"
    "onBtnExitProcessClicked()\0"
};

void RemoteCmdDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RemoteCmdDlg *_t = static_cast<RemoteCmdDlg *>(_o);
        switch (_id) {
        case 0: _t->onBtnWinExecClicked(); break;
        case 1: _t->onBtnExecuteConsoleCmdClicked(); break;
        case 2: _t->onBtnClearConsoleOutputClicked(); break;
        case 3: _t->onBtnExitProcessClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData RemoteCmdDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RemoteCmdDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RemoteCmdDlg,
      qt_meta_data_RemoteCmdDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RemoteCmdDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RemoteCmdDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RemoteCmdDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RemoteCmdDlg))
        return static_cast<void*>(const_cast< RemoteCmdDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int RemoteCmdDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
