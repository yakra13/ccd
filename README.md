## **Start your JQR [here](https://gitlab.90cos.cdl.af.mil/groups/90cos/virtual-job-qualification-records/current-bccd/ssgt-ziebarth-joshua/-/epics/1)**

-   You and your mentor should establish a working agreement on how you’ll accomplish the VJQR. Your working agreement can be found [here](working-agreement.md)
-   You can also start at the issue board, [here](https://gitlab.90cos.cdl.af.mil/groups/90cos/virtual-job-qualification-records/current-bccd/ssgt-ziebarth-joshua/-/boards)

# CCD Basic JQR v1.0

This repo contains your Virtual Job Qualification Record (VJQR) for the Cyber Capability Developer work role. The VJQR models the Job Qualification Record (JQR) and its Job Qualification Standards (JQS). You will use this repo to keep a record of all the work you do to demonstrate JQR line items, so we encourage you use [GitLab Flow](https://docs.gitlab.com/ee/topics/gitlab_flow.html) with your mentor as a reviewer to account for and close JQS line items (gitlab issues). If the JQS line item asks to demonstrate knowledge in some form, use the issue comment section to demonstrate this knowledge for your mentor.

## VJQR Structure

As a member of the 90COS, you will have a personal group titled as your `RANK FULLNAME` (it will be the parent group of this repo). This contains [GitLab Epics](https://docs.gitlab.com/ee/user/group/epics/) to structure and guide the mentor/mentee in the JQR process. A JQR will typically have multiple Job Qualification Standards (JQS), and each JQS will have many JQS line items. Using the Epic/Issue paradigm the JQR is mapped as the following

1. JQR -> GitLab Epic
2. JQS -> GitLab Child Epic
3. JQS line item -> GitLab Issues attached to Child Epics

It is highly recommended to use the [issue board](https://docs.gitlab.com/ee/user/project/issue_board.html#:~:text=%20Issue%20boardsall%20tiers%20%201%20Multiple%20issue,issues.%20It%20can%20have%20multiple%20lists...%20More%20) at the member group and the JQR project levels to accomplish and track issue progress.


## Automated Updates

The VJQR comes with a premade `.gitlab-ci.yml` which will update the JQR GitLab Epics and Issues description and material sections. This CI pipeline will only run
[if you trigger it manually](https://docs.gitlab.com/ee/ci/pipelines/#run-a-pipeline-manually) or [create a pipeline schedule](https://docs.gitlab.com/ee/ci/pipelines/schedules.html#add-a-pipeline-schedule). If you create a scheduled pipeline, you can run it at any frequency of your choosing (within reason).

## Feedback

If you wish to add new training material to the JQR, please communicate with your mentor to use the JQR viewer in the [DOT training application](https://training.staging.90cos.cdl.af.mil/). If you have any other feedback, please use the [Training and Eval Helpdesk](https://jira.90cos.cdl.af.mil/servicedesk/customer/portal/11) and submit feedback. You can also contact Rick Boone at `richard.boone.6@us.af.mil`
