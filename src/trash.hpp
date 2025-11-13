/**
 * @file    trash.hpp
 * @brief   Contains ctrash namespace.
 * 
 * Most stuff is in here, from trash_object typedef to
 * static functions that handle trashing,
 * to the trash_container object which holds trash 
 * locations and relevant metadata.
 */
#pragma once

#include <filesystem>
#include <sys/stat.h>

namespace ctrash
{
    /**
     * @brief typedef for stat struct (<sys/stat.h>).
     *
     * @param {dev_t}       st_dev      ID of device containing file
     * @param {ino_t}       st_ino      inode number
     * @param {mode_t}      st_mode     protection
     * @param {nlink_t}     st_nlink    number of hard links
     * @param {uid_t}       st_uid      user ID of owner
     * @param {gid_t}       st_gid      group ID of owner
     * @param {dev_t}       st_rdev     device ID (if special file)
     * @param {off_t}       st_size     total size, in bytes
     * @param {blksize_t}   st_blksize  blocksize for file system I/O
     * @param {blkcnt_t}    st_blocks   number of 512B blocks allocated
     * @param {time_t}      st_atime    time of last access
     * @param {time_t}      st_mtime    time of last modification
     * @param {time_t}      st_ctime    time of last status change
     */
    using trash_object = struct stat;

    /**
     * @brief holds metadata, location, and specific trash locations.
     *
     */
    class trash_container
    {
    private:
        std::string name;
        std::string description;

        std::filesystem::path location;
        std::filesystem::directory_iterator dir_it;

    public:
        // Basic Constructors
        trash_container();

        trash_container
        (
            std::string name,
            std::string description,
            std::filesystem::path location
        );

        explicit trash_container(std::filesystem::path location);

        // Copy-Move Constructors
        trash_container(const trash_container &other);

        trash_container(trash_container &&other) noexcept;

        // Destructor
        ~trash_container();
    };

    /**
     * @brief Static member functions to handle trash manipulation.
     *
     */
}
