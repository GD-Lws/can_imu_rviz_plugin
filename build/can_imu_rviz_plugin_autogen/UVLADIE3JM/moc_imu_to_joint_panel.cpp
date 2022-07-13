/****************************************************************************
** Meta object code from reading C++ file 'imu_to_joint_panel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../can_imu_rviz_plugin/src/imu_to_joint_panel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imu_to_joint_panel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel_t {
    QByteArrayData data[36];
    char stringdata0[564];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel_t qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel = {
    {
QT_MOC_LITERAL(0, 0, 41), // "imu_to_joint_rviz_plugin::Imu..."
QT_MOC_LITERAL(1, 42, 15), // "vci_obj_process"
QT_MOC_LITERAL(2, 58, 0), // ""
QT_MOC_LITERAL(3, 59, 11), // "VCI_CAN_OBJ"
QT_MOC_LITERAL(4, 71, 11), // "vci_can_obj"
QT_MOC_LITERAL(5, 83, 14), // "qt_layout_init"
QT_MOC_LITERAL(6, 98, 12), // "initImuTable"
QT_MOC_LITERAL(7, 111, 14), // "euler_callback"
QT_MOC_LITERAL(8, 126, 36), // "can_imu_lws::IMU_Euler_msg::C..."
QT_MOC_LITERAL(9, 163, 9), // "euler_msg"
QT_MOC_LITERAL(10, 173, 10), // "imu_id_set"
QT_MOC_LITERAL(11, 184, 9), // "startSpin"
QT_MOC_LITERAL(12, 194, 16), // "set_joint_offset"
QT_MOC_LITERAL(13, 211, 15), // "set_joint_state"
QT_MOC_LITERAL(14, 227, 24), // "sensor_msgs::JointState&"
QT_MOC_LITERAL(15, 252, 15), // "joint_state_msg"
QT_MOC_LITERAL(16, 268, 16), // "test_joint_state"
QT_MOC_LITERAL(17, 285, 16), // "imu_start_listen"
QT_MOC_LITERAL(18, 302, 15), // "joint_state_pub"
QT_MOC_LITERAL(19, 318, 15), // "euler_to_radian"
QT_MOC_LITERAL(20, 334, 5), // "euler"
QT_MOC_LITERAL(21, 340, 9), // "checkTest"
QT_MOC_LITERAL(22, 350, 12), // "checkSubLoad"
QT_MOC_LITERAL(23, 363, 12), // "checkChannel"
QT_MOC_LITERAL(24, 376, 15), // "open_can_device"
QT_MOC_LITERAL(25, 392, 16), // "close_can_device"
QT_MOC_LITERAL(26, 409, 22), // "can_device_config_init"
QT_MOC_LITERAL(27, 432, 4), // "Baud"
QT_MOC_LITERAL(28, 437, 16), // "can_start_listen"
QT_MOC_LITERAL(29, 454, 15), // "can_stop_listen"
QT_MOC_LITERAL(30, 470, 13), // "byte_to_short"
QT_MOC_LITERAL(31, 484, 6), // "H_data"
QT_MOC_LITERAL(32, 491, 6), // "L_data"
QT_MOC_LITERAL(33, 498, 17), // "euler_msg_process"
QT_MOC_LITERAL(34, 516, 26), // "can_imu_lws::IMU_Euler_msg"
QT_MOC_LITERAL(35, 543, 20) // "set_imu_euler_offset"

    },
    "imu_to_joint_rviz_plugin::ImuToJointPanel\0"
    "vci_obj_process\0\0VCI_CAN_OBJ\0vci_can_obj\0"
    "qt_layout_init\0initImuTable\0euler_callback\0"
    "can_imu_lws::IMU_Euler_msg::ConstPtr\0"
    "euler_msg\0imu_id_set\0startSpin\0"
    "set_joint_offset\0set_joint_state\0"
    "sensor_msgs::JointState&\0joint_state_msg\0"
    "test_joint_state\0imu_start_listen\0"
    "joint_state_pub\0euler_to_radian\0euler\0"
    "checkTest\0checkSubLoad\0checkChannel\0"
    "open_can_device\0close_can_device\0"
    "can_device_config_init\0Baud\0"
    "can_start_listen\0can_stop_listen\0"
    "byte_to_short\0H_data\0L_data\0"
    "euler_msg_process\0can_imu_lws::IMU_Euler_msg\0"
    "set_imu_euler_offset"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_imu_to_joint_rviz_plugin__ImuToJointPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  129,    2, 0x0a /* Public */,
       5,    0,  132,    2, 0x09 /* Protected */,
       6,    0,  133,    2, 0x09 /* Protected */,
       7,    1,  134,    2, 0x09 /* Protected */,
      10,    0,  137,    2, 0x09 /* Protected */,
      11,    0,  138,    2, 0x09 /* Protected */,
      12,    0,  139,    2, 0x09 /* Protected */,
      13,    1,  140,    2, 0x09 /* Protected */,
      16,    1,  143,    2, 0x09 /* Protected */,
      17,    0,  146,    2, 0x09 /* Protected */,
      18,    0,  147,    2, 0x09 /* Protected */,
      19,    1,  148,    2, 0x09 /* Protected */,
      21,    0,  151,    2, 0x09 /* Protected */,
      22,    0,  152,    2, 0x09 /* Protected */,
      23,    0,  153,    2, 0x09 /* Protected */,
      24,    0,  154,    2, 0x09 /* Protected */,
      25,    0,  155,    2, 0x09 /* Protected */,
      26,    1,  156,    2, 0x09 /* Protected */,
      28,    0,  159,    2, 0x09 /* Protected */,
      29,    0,  160,    2, 0x09 /* Protected */,
      30,    2,  161,    2, 0x09 /* Protected */,
      33,    1,  166,    2, 0x09 /* Protected */,
      35,    0,  169,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Float, QMetaType::Float,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, QMetaType::UChar, QMetaType::UChar,   31,   32,
    QMetaType::Void, 0x80000000 | 34,    9,
    QMetaType::Void,

       0        // eod
};

void imu_to_joint_rviz_plugin::ImuToJointPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImuToJointPanel *_t = static_cast<ImuToJointPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->vci_obj_process((*reinterpret_cast< VCI_CAN_OBJ(*)>(_a[1]))); break;
        case 1: _t->qt_layout_init(); break;
        case 2: _t->initImuTable(); break;
        case 3: _t->euler_callback((*reinterpret_cast< const can_imu_lws::IMU_Euler_msg::ConstPtr(*)>(_a[1]))); break;
        case 4: _t->imu_id_set(); break;
        case 5: _t->startSpin(); break;
        case 6: _t->set_joint_offset(); break;
        case 7: _t->set_joint_state((*reinterpret_cast< sensor_msgs::JointState(*)>(_a[1]))); break;
        case 8: _t->test_joint_state((*reinterpret_cast< sensor_msgs::JointState(*)>(_a[1]))); break;
        case 9: _t->imu_start_listen(); break;
        case 10: _t->joint_state_pub(); break;
        case 11: { float _r = _t->euler_to_radian((*reinterpret_cast< float(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->checkTest(); break;
        case 13: _t->checkSubLoad(); break;
        case 14: _t->checkChannel(); break;
        case 15: _t->open_can_device(); break;
        case 16: _t->close_can_device(); break;
        case 17: _t->can_device_config_init((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->can_start_listen(); break;
        case 19: _t->can_stop_listen(); break;
        case 20: { int _r = _t->byte_to_short((*reinterpret_cast< unsigned char(*)>(_a[1])),(*reinterpret_cast< unsigned char(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 21: _t->euler_msg_process((*reinterpret_cast< can_imu_lws::IMU_Euler_msg(*)>(_a[1]))); break;
        case 22: _t->set_imu_euler_offset(); break;
        default: ;
        }
    }
}

const QMetaObject imu_to_joint_rviz_plugin::ImuToJointPanel::staticMetaObject = {
    { &rviz::Panel::staticMetaObject, qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel.data,
      qt_meta_data_imu_to_joint_rviz_plugin__ImuToJointPanel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *imu_to_joint_rviz_plugin::ImuToJointPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *imu_to_joint_rviz_plugin::ImuToJointPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel.stringdata0))
        return static_cast<void*>(this);
    return rviz::Panel::qt_metacast(_clname);
}

int imu_to_joint_rviz_plugin::ImuToJointPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = rviz::Panel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 23;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
