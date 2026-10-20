- **`std:fs` rename, remove and atomic write (freeze item C4).** `rename(fs, source, target)`, `removeFile(fs, path)`,
  `removeDir(fs, path)` and `writeFileAtomic(fs, path, data)` return `Result<void, FsError>` over the new `std:fsraw`
  primitives. `FsErrorKind` gains `NotEmpty` (a `removeDir` of a directory with entries) and `FsOp` gains `OpRename` and
  `OpRemove`; the API snapshot `api/std/fs.api.txt` is updated.
