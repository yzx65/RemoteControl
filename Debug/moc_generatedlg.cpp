/****************************************************************************
** Meta object code from reading C++ file 'generatedlg.h'
**
** Created: Tue Mar 31 10:16:08 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../generatedlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'generatedlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GenerateDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      35,   30,   12,   12, 0x08,
      69,   12,   12,   12, 0x08,
      94,   88,   12,   12, 0x08,
     119,   88,   12,   12, 0x08,
     144,   12,   12,   12, 0x08,
     152,   12,   12,   12, 0x08,
     172,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GenerateDlg[] = {
    "GenerateDlg\0\0GenerateTarget()\0item\0"
    "PlatformChanged(QListWidgetItem*)\0"
    "GenerateFinished()\0index\0"
    "ServerTypeChanged_1(int)\0"
    "ServerTypeChanged_2(int)\0GetIP()\0"
    "RootStatusChanged()\0EnvironmentChanged()\0"
};

void GenerateDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GenerateDlg *_t = static_cast<GenerateDlg *>(_o);
        switch (_id) {
        case 0: _t->GenerateTarget(); break;
        case 1: _t->PlatformChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->GenerateFinished(); break;
        case 3: _t->ServerTypeChanged_1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->ServerTypeChanged_2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->GetIP(); break;
        case 6: _t->RootStatusChanged(); break;
        case 7: _t->EnvironmentChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GenerateDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GenerateDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GenerateDlg,
      qt_meta_data_GenerateDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GenerateDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GenerateDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GenerateDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GenerateDlg))
        return static_cast<void*>(const_cast< GenerateDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int GenerateDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
