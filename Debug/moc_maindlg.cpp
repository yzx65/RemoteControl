/****************************************************************************
** Meta object code from reading C++ file 'maindlg.h'
**
** Created: Tue Mar 31 10:16:07 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../maindlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maindlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      23,    8,    8,    8, 0x0a,
      36,    8,    8,    8, 0x0a,
      58,    8,    8,    8, 0x0a,
      71,    8,    8,    8, 0x0a,
      86,    8,    8,    8, 0x0a,
     101,    8,    8,    8, 0x0a,
     115,    8,    8,    8, 0x0a,
     132,    8,    8,    8, 0x0a,
     148,    8,    8,    8, 0x0a,
     168,    8,    8,    8, 0x0a,
     182,    8,    8,    8, 0x0a,
     203,    8,    8,    8, 0x0a,
     224,    8,    8,    8, 0x0a,
     246,    8,    8,    8, 0x0a,
     273,    8,    8,    8, 0x0a,
     286,    8,    8,    8, 0x0a,
     312,  300,    8,    8, 0x0a,
     345,  300,    8,    8, 0x0a,
     394,  388,    8,    8, 0x0a,
     437,  431,    8,    8, 0x0a,
     475,  431,    8,    8, 0x0a,
     516,    8,    8,    8, 0x0a,
     532,    8,    8,    8, 0x0a,
     555,  548,    8,    8, 0x0a,
     607,    8,    8,    8, 0x0a,
     647,  626,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainDlg[] = {
    "MainDlg\0\0StartAction()\0StopAction()\0"
    "MigrateDaemonAction()\0ExitAction()\0"
    "ConfigAction()\0PolicyAction()\0"
    "AliasAction()\0FavoriteAction()\0"
    "DelSelfAction()\0FlowControlAction()\0"
    "CleanAction()\0CreateTargetAction()\0"
    "CreateDaemonAction()\0CleanDatabaseAction()\0"
    "QueryDaemonAddressAction()\0HelpAction()\0"
    "AboutAction()\0item,column\0"
    "ShowTarget(QTreeWidgetItem*,int)\0"
    "CurrentTargetChanged(QTreeWidgetItem*,int)\0"
    "point\0onTrTargetContextMenuActived(QPoint)\0"
    "index\0onCmbCateGoryCurrentIndexChanged(int)\0"
    "onCmbDisplayModeCurrentIndexChanged(int)\0"
    "PNGTimerTimer()\0FlashTrayIcon()\0reason\0"
    "ProcessTrayEvent(QSystemTrayIcon::ActivationReason)\0"
    "ActiveMainWindow()\0pTarget,pluginNumber\0"
    "ModifyPluginPolicy(uint,int)\0"
};

void MainDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainDlg *_t = static_cast<MainDlg *>(_o);
        switch (_id) {
        case 0: _t->StartAction(); break;
        case 1: _t->StopAction(); break;
        case 2: _t->MigrateDaemonAction(); break;
        case 3: _t->ExitAction(); break;
        case 4: _t->ConfigAction(); break;
        case 5: _t->PolicyAction(); break;
        case 6: _t->AliasAction(); break;
        case 7: _t->FavoriteAction(); break;
        case 8: _t->DelSelfAction(); break;
        case 9: _t->FlowControlAction(); break;
        case 10: _t->CleanAction(); break;
        case 11: _t->CreateTargetAction(); break;
        case 12: _t->CreateDaemonAction(); break;
        case 13: _t->CleanDatabaseAction(); break;
        case 14: _t->QueryDaemonAddressAction(); break;
        case 15: _t->HelpAction(); break;
        case 16: _t->AboutAction(); break;
        case 17: _t->ShowTarget((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 18: _t->CurrentTargetChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 19: _t->onTrTargetContextMenuActived((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 20: _t->onCmbCateGoryCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->onCmbDisplayModeCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->PNGTimerTimer(); break;
        case 23: _t->FlashTrayIcon(); break;
        case 24: _t->ProcessTrayEvent((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 25: _t->ActiveMainWindow(); break;
        case 26: _t->ModifyPluginPolicy((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainDlg::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainDlg,
      qt_meta_data_MainDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainDlg))
        return static_cast<void*>(const_cast< MainDlg*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
