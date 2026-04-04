# BARQ (Burst Access Reader Queue) Implementation for ROS2 Nodes

## Future Upgrade?: futex-based notification system:
- Writer side: after the `front_idx.store(back, release)`
```cpp
syscall(SYS_futex, &header_->front_idx, FUTEX_WAKE, 1, nullptr, nullptr, 0);
```
- Reader side: instead of spin-polling `getLatest()`, the reader can block:
```cpp
syscall(SYS_futex, &header_->front_idx, FUTEX_WAIT, front, nullptr, nullptr, 0);
```
The kernel puts the thread to sleep until front_idx changes from old. Wake latency is ~1-2us.
This adds a syscall to the writer's hot path on every `write()/commit()` on a "Shoot and forget" philosophy. -> Make it optional?

## TODO:
- [ ] missing ARM non-temporal path (ARM NEON non temporal store intrinsics) for BARQ writer
- [x] study a signal system to advertise readers for new messages (e.g., futex or eventfd) - but this may add latency and complexity, so maybe not worth it

---
OG library author: Nabil Achir - https://github.com/achir-dev