mc_revo2
=========

This package provides a RobotModule implementation for the BrainCo Revo2 hand.

Dependencies
------------

This package requires:
- [mc_rtc](https://github.com/jrl-umi3218/mc_rtc)
- [revo2_description](https://github.com/isri-aist/revo2_description)

How to use
----------

Put the following in `mc_rtc.yaml`.

```yaml
MainRobot: Revo2_LeftHand
Timestep: 0.002
```

Available module names are:
- `Revo2`
- `Revo2_LeftHand`
- `Revo2_RightHand`
