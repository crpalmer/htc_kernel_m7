
void __diagfwd_dbg_raw_data(void *buf, const char *src, unsigned dbg_flag, unsigned mask)
{
	static char reason_str[128];
	int len;

	switch (dbg_flag) {
	case DIAG_DBG_READ:
		len = sprintf(reason_str, "Read Packet Data from %s", src);
		break;
	case DIAG_DBG_WRITE:
		len = sprintf(reason_str, "Write Packet Data to %s", src);
		break;
	case DIAG_DBG_DROP:
		len = sprintf(reason_str, "Drop Packet Data from %s", src);
		break;
	default:
		
		return;
	}

	if (mask || dbg_flag == DIAG_DBG_DROP) {
		
		len = sprintf(reason_str + len, "(%s)", "first 16 bytes");
#if DIAG_XPST
	} else if (driver->debug_dmbytes_recv > 0) {
		
		len = sprintf(reason_str + len, "(%s)", "for DM command");
		driver->debug_dmbytes_recv--;
#endif
	} else if (driver->qxdmusb_drop && driver->logging_mode == USB_MODE) {
		
		len = sprintf(reason_str + len, "(%s)", "Unknown packet");
	} else {
		
		return;
	}

	print_hex_dump(KERN_DEBUG, reason_str, 16, 1, DUMP_PREFIX_ADDRESS, buf, 16, 1);
}

