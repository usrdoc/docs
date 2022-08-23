#include <sys/modctl.h>
#include <sys/cmn_err.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/errno.h>
#include <sys/open.h>
#include <sys/cred.h>
#include <sys/uio.h>
#include <sys/conf.h>
#include <sys/devops.h>

/* Entry points */


static int dummy_attach(dev_info_t *dip, ddi_attach_cmd_t cmd);
static int dummy_detach(dev_info_t *dip, ddi_detach_cmd_t cmd);
static int dummy_getinfo(dev_info_t *dip, ddi_info_cmd_t cmd, void *arg,
			 void **resultp);
static int dummy_prop_op(dev_t dev, dev_info_t *dip, ddi_prop_op_t prop_op,
			 int flags, char *name, caddr_t valuep, int *lengthp);
static int dummy_open(dev_t *devp, int flag, int otyp, cred_t *cred_p);
static int dummy_close(dev_t dev, int flag, int otyp, cred_t *cred_p);
static int dummy_read(dev_t dev, struct uio *uiop, cred_t *cred_p);
static int dummy_write(dev_t dev, struct uio *uiop, cred_t *cred_p);


dev_info_t *dummy_dip;

static struct cb_ops dummy_cb_ops = {
	dummy_open,
	dummy_close,
	nodev,
	nodev,
	nodev,
	dummy_read,
	dummy_write,
	nodev,
	nodev,
	nodev,
	nodev,
	nochpoll,
	dummy_prop_op,
	NULL,
	D_NEW | D_MP,
	CB_REV,
	nodev,
	nodev
};

static struct dev_ops dummy_dev_ops = {
	DEVO_REV,
	0,
	dummy_getinfo,
	nulldev,
	nulldev,
	dummy_attach,
	dummy_detach,
	nodev,
	&dummy_cb_ops,
	(struct bus_ops *)NULL,
	nodev,
	ddi_quiesce_not_needed
};

static struct modldrv md = {
	&mod_driverops,
	"dummy driver",
	&dummy_dev_ops
};

static struct modlinkage ml = {
	MODREV_1,
	&md,
	NULL
};

int
_init(void)
{
	cmn_err(CE_NOTE, "Inside _init");
	return (mod_install(&ml));
}

int
_info(struct modinfo *modinfop)
{
	cmn_err(CE_NOTE, "Inside _info");
	return(mod_info(&ml, modinfop));
}

int
_fini(void)
{
	cmn_err(CE_NOTE, "Inside _fini");
	return(mod_remove(&ml));
}

/* Device autoconfiguration */
static int
dummy_attach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	cmn_err(CE_NOTE, "Inside dummy_attach");
	switch(cmd) {
	case DDI_ATTACH:
		dummy_dip = dip; /* Where is this guy declared and defined? */
		if (ddi_create_minor_node(dip, "0", S_IFCHR,
					  ddi_get_instance(dip), DDI_PSEUDO,
					  0) != DDI_SUCCESS) {
			cmn_err(CE_NOTE, "%s%d: attach: could not add character"
				" node", "dummy", 0);
			return(DDI_FAILURE);
		} else
			return(DDI_SUCCESS);
	default:
		return(DDI_FAILURE);
	}
}

static int
dummy_detach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	cmn_err(CE_NOTE, "Inside dummy_detach");
	switch(cmd) {
	case DDI_DETACH:
		dummy_dip = 0;
		ddi_remove_minor_node(dip, NULL);
		return(DDI_SUCCESS);
	default:
		return(DDI_FAILURE);
	}
}
	
static int
dummy_getinfo(dev_info_t *dip, ddi_info_cmd_t cmd, void *arg, void **resultp)
{
	cmn_err(CE_NOTE, "Inside dummy_getinfo");
	switch(cmd) {
	case DDI_INFO_DEVT2DEVINFO:
		*resultp = dummy_dip;
		return(DDI_SUCCESS);
	case DDI_INFO_DEVT2INSTANCE:
		*resultp = 0;
		return(DDI_SUCCESS);
	default:
		return(DDI_FAILURE);
	}
}

static int
dummy_prop_op(dev_t dev, dev_info_t *dip, ddi_prop_op_t prop_op,
	      int flags, char *name, caddr_t valuep, int *lengthp)
{
	cmn_err(CE_NOTE, "Inside dummy_prop_op");
	return(ddi_prop_op(dev, dip, prop_op, flags, name, valuep, lengthp));
}

static int dummy_open(dev_t *devp, int flag, int otyp, cred_t *cred)
{
	cmn_err(CE_NOTE, "Inside dummy_open");
	return(DDI_SUCCESS);
}

static int
dummy_close(dev_t dev, int flag, int otyp, cred_t *cred)
{
	cmn_err(CE_NOTE, "Inside dummy_close");
	return(DDI_SUCCESS);
}

static int
dummy_read(dev_t dev, struct uio *uiop, cred_t *credp)
{
	cmn_err(CE_NOTE, "Inside dummy_read");
	return(DDI_SUCCESS);
}

static int
dummy_write(dev_t dev, struct uio *uiop, cred_t *credp)
{
	cmn_err(CE_NOTE, "Inside dummy_write");
	return(DDI_SUCCESS);
}
