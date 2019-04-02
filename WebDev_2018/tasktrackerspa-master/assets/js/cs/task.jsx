import React from 'react';
import { Card, CardBody } from 'reactstrap';

export default function Task(params) {
  let task = params.task;
  return <Card>
    <CardHeader>
        <p>{ task.title }</p>
        <p>{ task.completed ? "complete" : "incomplete" }</p>
    </CardHeader>
    <CardBody>
      <div>
        <p>Assigned to <b>{ task.user.name }</b></p>
        <p>{ task.description }</p>
        <p> { task.completed ? "Took " + task.time + " min" : ""}</p>
      </div>
    </CardBody>
  </Card>;
}